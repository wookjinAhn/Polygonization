//
// Created by wj on 22. 9. 1.
//

#include "ConvexHull.hpp"

ConvexHull::ConvexHull()
{
}

ConvexHull::ConvexHull(std::vector<camelVector::Point3D>& inputPoint)
{
    mInputData = inputPoint;
}

void ConvexHull::SetInputData(std::vector<camelVector::Point3D>& inputPoint)
{
    mInputData = inputPoint;
}

std::vector<camelVector::Point3D> ConvexHull::GetInputData() const
{
    return mInputData;
}

void ConvexHull::SetOutputData(std::vector<camelVector::Point3D>& outPoint)
{
    mOutputData = outPoint;
}

std::vector<camelVector::Point3D> ConvexHull::GetOutputData() const
{
    return mOutputData;
}

void ConvexHull::Run()
{

}

camelVector::Point3D ConvexHull::nextToTop(std::stack<camelVector::Point3D>& pointStack)
{
    camelVector::Point3D point = pointStack.top();
    pointStack.pop();
    camelVector::Point3D result = pointStack.top();
    pointStack.push(point);
    return result;
}

void ConvexHull::swap(camelVector::Point3D& point1, camelVector::Point3D& point2)
{
    camelVector::Point3D temp = point1;
    point1 = point2;
    point2 = temp;
}

int ConvexHull::distSq(camelVector::Point3D point1, camelVector::Point3D point2)
{
    return (point1.GetX() - point2.GetX()) * (point1.GetX() - point2.GetX()) +
           (point1.GetZ() - point2.GetZ()) * (point1.GetZ() - point2.GetZ());
}

int ConvexHull::orientation(camelVector::Point3D p, camelVector::Point3D q, camelVector::Point3D r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // collinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

int ConvexHull::compare(const void* vp1, const void* vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

    return (o == 2)? -1: 1;
}

void ConvexHull::convexHull(std::vector<camelVector::Point3D> points)
{
// Find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;

        // Pick the bottom-most or choose the left
        // most point in case of tie
        if ((y < ymin) || (ymin == y &&
                           points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Place the bottom-most point at first position
    swap(points[0], points[min]);

    // Sort n-1 points with respect to the first point.
    // A point p1 comes before p2 in sorted output if p2
    // has larger polar angle (in counterclockwise
    // direction) than p1
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(Point), compare);

    // If two or more points make same angle with p0,
    // Remove all but the one that is farthest from p0
    // Remember that, in above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have same angle.
    int m = 1; // Initialize size of modified array
    for (int i=1; i<n; i++)
    {
        // Keep removing i while angle of i and i+1 is same
        // with respect to p0
        while (i < n-1 && orientation(p0, points[i],
                                      points[i+1]) == 0)
            i++;


        points[m] = points[i];
        m++;  // Update size of modified array
    }

    // If modified array of points has less than 3 points,
    // convex hull is not possible
    if (m < 3) return;

    // Create an empty stack and push first three points
    // to it.
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Process remaining n-3 points
    for (int i = 3; i < m; i++)
    {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    // Now stack has the output points, print contents of stack
    while (!S.empty())
    {
        Point p = S.top();
        cout << "(" << p.x << ", " << p.y <<")" << endl;
        S.pop();
    }
}