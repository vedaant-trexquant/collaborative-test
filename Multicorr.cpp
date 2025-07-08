#include <cmath>
#include <vector>
#include <algorithm>

float corr(const std::vector<float> &v1, const std::vector<float> &v2)
{
    float mean1 = .0f, sum1sq = .0f, mean2 = .0f, sum2sq = .0f;
    for (size_t i = 0; i < v1.size(); ++i)
    {
        mean1 += (v1[i] / v1.size());
        mean2 += (v2[i] / v2.size());
    }

    float sumcov = .0f;

    for (size_t i = 0; i < v1.size(); ++i)
    {
        float diff1 = v1[i] - mean1;
        float diff2 = v2[i] - mean2;
        sum1sq += diff1 * diff1;
        sum2sq += diff2 * diff2;

        sumcov += diff1 * diff2;
    }

    return sumcov / std::sqrt(sum1sq * sum2sq);
}

void select_vecs(const std::vector<std::vector<float>> &mat, std::vector<size_t> &selected, float threshold)
{
    for (size_t i = 0; i < mat.size(); ++i)
    {
        bool good = true;
        for (size_t j : selected)
        {
            float correlation = corr(mat[i], mat[j]);
            if (correlation > threshold)
            {
                good = false;
                break;
            }
        }

        if (good)
        {
            selected.push_back(i);
        }
    }
}