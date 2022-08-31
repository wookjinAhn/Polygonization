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
    quickHull();
}

void QuickHull::quickHull()
{
    std::sort(mInputData.begin(), mInputData.end(), camelVector::Point3D::AscendingByX);
    int max

}

void QuickHull::findHull()
{

}