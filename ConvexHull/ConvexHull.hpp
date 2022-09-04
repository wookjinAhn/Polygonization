//
// Created by wj on 22. 9. 1.
//

#ifndef POLYGONIZATION_CONVEXHULL_HPP
#define POLYGONIZATION_CONVEXHULL_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include "../Point/Point3D.hpp"

class ConvexHull
{
public:
    ConvexHull();
    ConvexHull(std::vector<camel::Point3D>& inputPoint);

    void SetInputData(std::vector<camel::Point3D>& inputPoint);
    std::vector<camel::Point3D> GetInputData() const;

    void SetOutputData(std::vector<camel::Point3D>& outPoint);
    std::vector<camel::Point3D> GetOutputData() const;

    void Run();

private:
    void setInitialPoint();
    void getAngleEachPoints();
    static bool DescendingByAngle(camel::Point3D& firstPoint, camel::Point3D& secondPoint);
    void sortByAngle();
    void convexHull();

    std::vector<camel::Point3D> mInputData;
    std::vector<camel::Point3D> mOutputData;

    camel::Point3D mInitialPoint;
};


#endif //POLYGONIZATION_CONVEXHULL_HPP

