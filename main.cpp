#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <chrono>
#include <camel-euclid/Point3D.hpp>
#include "QuickHull/QuickHull.hpp"
#include "ConvexHull/ConvexHull.hpp"

void fromPCD(std::vector<camelVector::Point3D>& data, int file)
{
    std::ifstream fin;
    std::string filePath = "/home/wj/Desktop/Data/polygonize/" + std::to_string(file) + ".pcd";
    fin.open(filePath);
    std::string line;

    if (fin.is_open())
    {
        int num = 1;
        while (!fin.eof())
        {
            getline(fin, line);
            if (num > 10)
            {
                float dataX, dataY, dataZ;
                std::istringstream iss(line);
                iss >> dataX >> dataY >> dataZ;
                camelVector::Point3D point = { dataX, dataY, dataZ };
                data.push_back(point);
            }
            num++;
        }
    }
    fin.close();
}

void toPCD(std::vector<camelVector::Point3D>& data)
{
    std::cout << "output : " << data.size() << std::endl;
    std::string outputPath = "/home/wj/Desktop/Data/polygonize/output/";
    time_t t;
    struct tm* timeinfo;
    time(&t);
    timeinfo = localtime(&t);

    std::string hour, min;

    if (timeinfo->tm_hour < 10) hour = "0" + std::to_string(timeinfo->tm_hour);
    else hour = std::to_string(timeinfo->tm_hour);

    if (timeinfo->tm_min < 10) min = "0" + std::to_string(timeinfo->tm_min);
    else min = std::to_string(timeinfo->tm_min);

    std::string filePath = outputPath + hour + min + ".pcd";

    std::ofstream fout;
    fout.open(filePath);

    fout << "VERSION" << std::endl;
    fout << "FIELDS x y z" << std::endl;
    fout << "SIZE 4 4 4" << std::endl;
    fout << "TYPE F F F" << std::endl;
    fout << "COUNT 1 1 1" << std::endl;
    fout << "WIDTH 1" << std::endl;
    fout << "HEIGHT " << data.size() << std::endl;
    fout << "VIEWPOINT 0 0 0 1 0 0 0" << std::endl;
    fout << "POINTS " << data.size() << std::endl;
    fout << "DATA ascii" << std::endl;

    for (int i = 0; i < data.size(); i++)
    {
        fout << data[i].GetX() << " " << data[i].GetY() << " " << data[i].GetZ() << "\n";
    }

    fout.close();
}

int main()
{
    const auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<camelVector::Point3D> inputData;
    fromPCD(inputData, 336);

    QuickHull quickHull;
    quickHull.SetInputData(inputData);
    std::cout << quickHull.GetInputData().size() << std::endl;
    quickHull.Run();

    std::cout << quickHull.GetOutputData().size() << std::endl;

    std::vector<camelVector::Point3D> outputData = quickHull.GetOutputData();
    toPCD(outputData);

    const auto stopTime = std::chrono::high_resolution_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
    std::cout << elapsedTime.count() << " us." << std::endl;
}