//
// Created by wj on 22. 8. 30.
//

#ifndef POLYGONIZATION_QUICKHULL_HPP
#define POLYGONIZATION_QUICKHULL_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include "../Point/Point3D.hpp"

class QuickHull
{
public:
    QuickHull();
    QuickHull(std::vector<camel::Point3D>& inputPoint);

    void SetInputData(std::vector<camel::Point3D>& inputPoint);
    std::vector<camel::Point3D> GetInputData() const;

    void SetOutputData(std::vector<camel::Point3D>& outPoint);
    std::vector<camel::Point3D> GetOutputData() const;

    void Run();

private:
    int findSide(camel::Point3D point1, camel::Point3D point2, camel::Point3D point);
    float lineDist(camel::Point3D point1, camel::Point3D point2, camel::Point3D point);
    void quickHull(const std::vector<camel::Point3D>& data, camel::Point3D point1, camel::Point3D point2, int side);

    void getAngleEachPoints();
    static bool DescendingByAngle(camel::Point3D& firstPoint, camel::Point3D& secondPoint);
    void sortByAngle();

    std::vector<camel::Point3D> mInputData;
    std::vector<camel::Point3D> mOutputData;

    camel::Point3D mInitialPoint;
};


#endif //POLYGONIZATION_QUICKHULL_HPP
