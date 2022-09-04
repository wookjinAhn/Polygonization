//
// Created by wj on 22. 9. 1.
//

#include "ConvexHull.hpp"

ConvexHull::ConvexHull()
{
}

ConvexHull::ConvexHull(std::vector<camel::Point3D>& inputPoint)
{
    mInputData = inputPoint;
}

void ConvexHull::SetInputData(std::vector<camel::Point3D>& inputPoint)
{
    mInputData = inputPoint;
}

std::vector<camel::Point3D> ConvexHull::GetInputData() const
{
    return mInputData;
}

void ConvexHull::SetOutputData(std::vector<camel::Point3D>& outPoint)
{
    mOutputData = outPoint;
}

std::vector<camel::Point3D> ConvexHull::GetOutputData() const
{
    return mOutputData;
}

void ConvexHull::Run()
{
    setInitialPoint();
    getAngleEachPoints();
    sortByAngle();
    convexHull();
}

void ConvexHull::setInitialPoint()
{
    std::cout << "setInitialPoint() mInputData : " << mInputData.size() << std::endl;
    std::sort(mInputData.begin(), mInputData.end(), camel::Point3D::AscendingByZ);
    mInitialPoint = mInputData[0];
    mInputData.erase(mInputData.begin() + 0);
    std::cout << "setInitialPoint() mInitialPoint : " << mInitialPoint.GetX() << ", " << mInitialPoint.GetY() << ", " << mInitialPoint.GetZ()  << std::endl;
    std::cout << "setInitialPoint() mInputData: " << mInputData.size() << " : " << mInputData[0].GetX() << ", " << mInputData[0].GetY() << ", " << mInputData[0].GetZ()  << std::endl;
}

void ConvexHull::getAngleEachPoints()
{
    std::vector<float> angles;
    for (int i = 0; i < mInputData.size(); i++)
    {
        float angle = std::atan2(mInputData[i].GetX() - mInitialPoint.GetX(), mInputData[i].GetZ() - mInitialPoint.GetZ());
        float distance = mInputData[i].DistanceBetweenOther(mInitialPoint);
        mInputData[i].SetAngle(angle);
        mInputData[i].SetDistance(distance);
    }
}

 bool ConvexHull::DescendingByAngle(camel::Point3D& firstPoint, camel::Point3D& secondPoint)
{
    if (firstPoint.GetAngle() == secondPoint.GetAngle())
    {
        return firstPoint.GetDistance() > secondPoint.GetDistance();
    }
    else
    {
        return firstPoint.GetAngle() > secondPoint.GetAngle();
    }
}

void ConvexHull::sortByAngle()
{
    std::sort(mInputData.begin(), mInputData.end(), DescendingByAngle);
}

void ConvexHull::convexHull()
{

}