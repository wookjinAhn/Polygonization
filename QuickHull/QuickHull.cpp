//
// Created by wj on 22. 8. 30.
//

#include "QuickHull.hpp"

QuickHull::QuickHull()
{
}

QuickHull::QuickHull(std::vector<camelVector::Point3D>& inputPoint)
{
    mInputData = inputPoint;
}

void QuickHull::SetInputData(std::vector<camelVector::Point3D>& inputPoint)
{
    mInputData = inputPoint;
}

std::vector<camelVector::Point3D> QuickHull::GetInputData() const
{
    return mInputData;
}

void QuickHull::SetOutputData(std::vector<camelVector::Point3D>& outPoint)
{
    mOutputData = outPoint;
}

std::vector<camelVector::Point3D> QuickHull::GetOutputData() const
{
    return mOutputData;
}

void QuickHull::Run()
{
    if (mInputData.size() < 3)
    {
        std::cout << "Convex hull not possible" << std::endl;
        return;
    }

    // Finding the point with minimum and
    // maximum x-coordinate
    int min_x = 0, max_x = 0;
    for (int i=1; i<mInputData.size(); i++)
    {
        if (mInputData[i].GetX() < mInputData[min_x].GetX())
            min_x = i;
        if (mInputData[i].GetX() > mInputData[max_x].GetX())
            max_x = i;
    }

    quickHull(mInputData, mInputData[min_x], mInputData[max_x], 1);
    quickHull(mInputData, mInputData[min_x], mInputData[max_x], -1);
}

int QuickHull::findSide(camelVector::Point3D point1, camelVector::Point3D point2, camelVector::Point3D point)
{
    float val = (point.GetZ() - point1.GetZ()) * (point2.GetX() - point1.GetX()) -
              (point2.GetZ() - point1.GetZ()) * (point.GetX() - point1.GetX());

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

float QuickHull::lineDist(camelVector::Point3D point1, camelVector::Point3D point2, camelVector::Point3D point)
{
    return std::abs((point.GetZ() - point1.GetZ()) * (point2.GetX() - point1.GetX()) -
                (point2.GetZ() - point1.GetZ()) * (point.GetX() - point1.GetX()));
}

void QuickHull::quickHull(const std::vector<camelVector::Point3D>& data, camelVector::Point3D point1, camelVector::Point3D point2, int side)
{
    int ind = -1;
    float max_dist = 0.0f;

    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i=0; i<data.size(); i++)
    {
        float temp = lineDist(point1, point2, data[i]);
        if (findSide(point1, point2, data[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }

    // If no point is found, add the end points
    // of L to the convex hull.
    if (ind == -1)
    {
        mOutputData.push_back(point1);
        mOutputData.push_back(point2);
        return;
    }

    // Recur for the two parts divided by a[ind]
    quickHull(data, data[ind], point1, -findSide(data[ind], point1, point2));
    quickHull(data, data[ind], point2, -findSide(data[ind], point2, point1));
}