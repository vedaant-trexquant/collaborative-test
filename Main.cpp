#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

void select_vecs(const std::vector<std::vector<float>> &mat, std::vector<size_t> &selected, float threshold);

const std::string inputFile = "vectors.mat";
const std::string outputFile = "selected.arr";
const int vCount = 10'000;
const int vSize = 1'000;

void check_open(std::ifstream &file, const std::string &filename)
{
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }
}

int main()
{
    std::ifstream ifile(inputFile);
    std::ifstream ofile(outputFile);
    check_open(ifile, inputFile);
    check_open(ofile, outputFile);

    std::vector<std::vector<float>> mat(vCount, std::vector<float>(vSize));
    std::vector<size_t> selected;

    for (size_t i = 0; i < vCount; i++)
    {
        if (!ofile.eof())
        {
            selected.push_back(0);
            ofile >> selected[i];
        }

        for (size_t j = 0; j < vSize; j++)
        {
            ifile >> mat[i][j];
            if (ifile.fail())
            {
                std::cerr << "Error reading data from file." << std::endl;
                return 1;
            }
        }
    }

    ifile.close();

    std::vector<size_t> result;

    auto start = std::chrono::high_resolution_clock::now();

    select_vecs(mat, result, 0.05f);

    auto end = std::chrono::high_resolution_clock::now();

    bool pass = true;
    if (result.size() != selected.size())
    {
        std::cerr << "Size mismatch: expected " << selected.size() << ", got " << result.size() << std::endl;
        pass = false;
    }

    for (size_t i = 0; i < std::min(selected.size(), result.size()); ++i)
    {
        if (selected[i] != result[i])
        {
            std::cerr << "Mismatch at index " << i << ": expected " << selected[i] << ", got " << result[i] << std::endl;
            pass = false;
        }
    }

    if (pass)
    {
        std::cout << "PASS" << std::endl;
    }
    else
    {
        std::cout << "FAIL" << std::endl;
    }

    std::cout << "Time taken: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;
    return 0;
}