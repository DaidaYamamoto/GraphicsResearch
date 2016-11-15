#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <random>
#include <string>
#include <filesystem> // std::tr2::sys::path etc.
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define STORE_FOR_LEARNING (1)


void ImageDistributerForCrowdFlower()
{
    int flags[37];
    for (size_t i = 0; i < 37; i++)
        flags[i] = 1;
    flags[0] = 4; // beast
    flags[1] = 2; // robot
    flags[2] = 3; // chicken
    flags[3] = 4; // worm
    flags[14] = 2;
    flags[18] = 2;
    flags[19] = 2;

    // random seed is not used on this program
    std::default_random_engine generator(0xdeadbeaf);
    std::uniform_real_distribution<float> distribution(0.0, 0.9999f);

    const int width = 1280;
    const int image_size = 720;

    char searchPath[256];
    sprintf_s(searchPath, sizeof(searchPath), "../final_images/captured/");
    std::tr2::sys::recursive_directory_iterator it(searchPath), end;
    for (; it != end; it++)
    {
        std::string s_filepath = it->path().filename();
        const char* filename = s_filepath.c_str();

        int dummy[8];
        int characterId;
        int result = sscanf(filename, "%d_%d_%d_%d_%d_%d_%d_%d.png",
            &dummy[0], &dummy[1], &dummy[2], &dummy[3], &characterId, &dummy[5], &dummy[6], &dummy[7]);

        if (dummy[2] != 0)
            continue;

        static int idx2 = 0;
        idx2++;
        const int CONST_RATIO = 50*3;

#if STORE_FOR_LEARNING
        int ratio = CONST_RATIO / flags[characterId];
        if (ratio == 0) ratio = 1;
        if (idx2 % ratio != 0)
        {
            continue;
        }
#else
        if (idx2 % 5 == 0)
        {
            continue;
        }
#endif

        for (size_t i = 0; i < 9; i++)
        {
            char filepath[256];
            sprintf(filepath, "../final_images/captured/%.5d_%d_%d_%.5d_%.2d_%d_%.3d_%.3d.png",
                dummy[0], dummy[1], i, dummy[3], characterId, dummy[5], dummy[6], dummy[7]);

            cv::Mat source_image = cv::imread(filepath, CV_LOAD_IMAGE_COLOR);
            if (source_image.data == NULL)
            {
                printf("can not load %s\n", filepath);
            }
            cv::Mat dump_image(image_size, image_size, CV_8UC3);

            int idx1 = 0;
            int offset = (width - image_size) / 2;
            for (int y = 0; y < image_size; y++)
            {
                for (int x = offset; x < image_size + offset; x++)
                {
                    dump_image.data[idx1 * 3 + 0] = source_image.data[(x + y * width) * 3 + 0];
                    dump_image.data[idx1 * 3 + 1] = source_image.data[(x + y * width) * 3 + 1];
                    dump_image.data[idx1 * 3 + 2] = source_image.data[(x + y * width) * 3 + 2];
                    idx1++;
                }
            }

            std::vector<uchar> buff;// buffer for coding
            std::vector<int> param = std::vector<int>(2);
            param[0] = CV_IMWRITE_JPEG_QUALITY;
            param[1] = 90;

            // pass 20% of images
#if STORE_FOR_LEARNING
            sprintf(filepath, "../final_images/crowdflower/000/%.5d_%d_%d_%.5d_%.2d_%d_%.3d_%.3d.jpg",                
                dummy[0], dummy[1], i, dummy[3], characterId, dummy[5], dummy[6], dummy[7]);
            cv::imwrite(filepath, dump_image, param);
#else
            sprintf(filepath, "../final_images/crowdflower/001/%.5d_%d_%d_%.5d_%.2d_%d_%.3d_%.3d.jpg",
                dummy[0], dummy[1], i, dummy[3], dummy[4], dummy[5], dummy[6], dummy[7]);
            cv::imwrite(filepath, dump_image, param);
#endif
        }
    }
}
