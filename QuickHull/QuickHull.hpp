//
// Created by wj on 22. 8. 30.
//

#ifndef POLYGONIZATION_QUICKHULL_HPP
#define POLYGONIZATION_QUICKHULL_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <camel-euclid/Vector.hpp>

class QuickHull
{
public:
    QuickHull();
    QuickHull(std::vector<camelVector::Point3D>& inputPoint);

    void SetInputData(std::vector<camelVector::Point3D>& inputPoint);
    std::vector<camelVector::Point3D> GetInputData() const;

    void SetOutputData(std::vector<camelVector::Point3D>& outPoint);
    std::vector<camelVector::Point3D> GetOutputData() const;

    void Run();

private:
    int findSide(camelVector::Point3D point1, camelVector::Point3D point2, camelVector::Point3D point);
    float lineDist(camelVector::Point3D point1, camelVector::Point3D point2, camelVector::Point3D point);
    void quickHull(const std::vector<camelVector::Point3D>& data, camelVector::Point3D point1, camelVector::Point3D point2, int side);

    std::vector<camelVector::Point3D> mInputData;
    std::vector<camelVector::Point3D> mOutputData;
};


#endif //POLYGONIZATION_QUICKHULL_HPP
