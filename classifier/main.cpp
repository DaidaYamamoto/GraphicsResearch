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

#include "main.h"

const int NUM_CSV_FILE = 1;

struct UserScore{
    float averageScore{ 0.0f };
    float totalScore{ 0.0f};
    int counter{ 0 };
};

struct BanUser{
    bool banFlag{ false };
};

void AnalyzeCsvFile()
{
    std::unordered_map<std::string, UserScore> userScoreList;
    std::unordered_map<std::string, BanUser> banUserList;

    // scan image list
    {
        char searchPath[256];
        sprintf_s(searchPath, sizeof(searchPath), "../final_images/crowdflower/banUserList.txt");

        std::ifstream ifs(searchPath);

        if (!ifs) {
            printf("Cannot open file [%s]", searchPath);
            exit(0);
        }

        const int MAX_CHARS = 8192;  // Alloc enough size.
        std::vector<char> buf(MAX_CHARS);

        while (ifs.peek() != -1) {
            ifs.getline(&buf[0], MAX_CHARS);
            std::string linebuf(&buf[0]);

            // Skip if empty line.
            if (linebuf.empty()) {
                continue;
            }

            char* token = (char*)(linebuf.c_str());
            char userID[256];
            sscanf_s(token, "%s\n", userID, sizeof(userID));

            banUserList[userID].banFlag = true;
        }
    }

    // loop csv file
    for (size_t i = 0; i < NUM_CSV_FILE; i++)
    {
        char searchPath[256];
        sprintf_s(searchPath, sizeof(searchPath), "../final_images/crowdflower/judgement%.3d.csv", i);

        std::ifstream ifs(searchPath);

        if (!ifs) {
            printf("Cannot open file [%s]", searchPath);
            continue;
        }

        const int MAX_CHARS = 8192;  // Alloc enough size.
        std::vector<char> buf(MAX_CHARS);

        while (ifs.peek() != -1) {
            ifs.getline(&buf[0], MAX_CHARS);
            std::string linebuf(&buf[0]);

            // Skip if empty line.
            if (linebuf.empty()) {
                continue;
            }

            char* token = (char*)(linebuf.c_str());

            // Skip if first line.
            if ((0 == strncmp(token, "WorkerID", 6))) {
                continue;
            }

            int dummy[2];
            int LOD;
            char userID[256], YesOrNo[16], filename[1024];

            char *s = strtok(token, ",");
            sscanf_s(s, "%s\n", userID, sizeof(userID));
            s = strtok(NULL, ",");
            sscanf_s(s, "%d\n", &dummy[0]);
            s = strtok(NULL, ",");
            sscanf_s(s, "%d\n", &dummy[1]);
            s = strtok(NULL, ",");
            sscanf_s(s, "%d\n", &LOD);
            s = strtok(NULL, ",");
            sscanf_s(s, "%s\n", YesOrNo, sizeof(YesOrNo));
            s = strtok(NULL, ",");
            sscanf_s(s, "%s\n", filename, sizeof(filename));

            if (banUserList[userID].banFlag == true)
                continue;

            userScoreList[filename].counter++;
            if ( strcmp(YesOrNo, "Yes") == 0 )
            {
                userScoreList[filename].totalScore += 0.0f;
                userScoreList[filename].averageScore = userScoreList[filename].totalScore / static_cast<float>(userScoreList[filename].counter);
            }
            else if (strcmp(YesOrNo, "No") == 0)
            {
                userScoreList[filename].totalScore += 1.0f;
                userScoreList[filename].averageScore = userScoreList[filename].totalScore / static_cast<float>(userScoreList[filename].counter);
            }
        }
    }

    // dump all summary
    {
        char searchPath[256];
        sprintf_s(searchPath, sizeof(searchPath), "../final_images/crowdflower/merged.csv");
        FILE* fp = fopen(searchPath, "w");

        for (auto it = userScoreList.begin(); it != userScoreList.end(); ++it)
        {
            fprintf(fp, "%s,%f,%d\n", it->first.c_str(), it->second.averageScore, it->second.counter);
        }

        fclose(fp);
    }
    exit(0);
}

const int NUM_VERIFY_IMAGE = 100;

void DumpImageListForBan()
{
    FILE* fp_imageList = fopen("../final_images/crowdflower/ban/imageListForBan.txt", "w");
    FILE* fp_imageCopyBatch = fopen("../final_images/crowdflower/ban/batch.bat", "w");

    // dump all images
    for (size_t i = 0; i < 2; i++){
        char searchPath[256];

        if (i == 0)
            sprintf_s(searchPath, sizeof(searchPath), "../final_images/crowdflower/ban/mergedDiffSorted.csv");
        else
            sprintf_s(searchPath, sizeof(searchPath), "../final_images/crowdflower/ban/mergedSameSorted.csv");
        FILE* fp_csv = fopen(searchPath, "r");

        std::ifstream ifs(searchPath);

        if (!ifs) {
            printf("Cannot open file [%s]", searchPath);
            continue;
        }

        const int MAX_CHARS = 8192;  // Alloc enough size.
        std::vector<char> buf(MAX_CHARS);

        for (size_t j = 0; j < NUM_VERIFY_IMAGE; j++)
        {
            ifs.getline(&buf[0], MAX_CHARS); 
            std::string linebuf(&buf[0]);

            char* token = (char*)(linebuf.c_str());

            int sceneIdx, rotateIdx, lodIdx, count;
            char filenameAppend[256];
            float score;

            char *s = strtok(token, "_");
            sscanf_s(s, "%d\n", &sceneIdx);
            s = strtok(NULL, "_");
            sscanf_s(s, "%d\n", &rotateIdx);
            s = strtok(NULL, "_");
            sscanf_s(s, "%d\n", &lodIdx);
            s = strtok(NULL, ",");
            sscanf_s(s, "%s\n", filenameAppend);
            s = strtok(NULL, ",");
            sscanf_s(s, "%f\n", &score);
            s = strtok(NULL, ",");
            sscanf_s(s, "%d\n", &count);

            fprintf(fp_imageList, "%.5d_%d_%d_%s %d\n", sceneIdx, rotateIdx, lodIdx, filenameAppend, i);
            if (i == 0)
            {
                fprintf(fp_imageCopyBatch, "cp ../000/%.5d_%d_%d_%s ./bad_images/%.5d_%d_%d_%s\n", sceneIdx, rotateIdx, lodIdx, filenameAppend, sceneIdx, rotateIdx, lodIdx, filenameAppend);
                fprintf(fp_imageCopyBatch, "cp ../000/%.5d_%d_0_%s ./bad_images/%.5d_%d_0_%s\n", sceneIdx, rotateIdx, filenameAppend, sceneIdx, rotateIdx, filenameAppend);
            }
            else if (i == 1)
            {
                fprintf(fp_imageCopyBatch, "cp ../000/%.5d_%d_%d_%s ./good_images/%.5d_%d_%d_%s\n", sceneIdx, rotateIdx, lodIdx, filenameAppend, sceneIdx, rotateIdx, lodIdx, filenameAppend);
                fprintf(fp_imageCopyBatch, "cp ../000/%.5d_%d_0_%s ./good_images/%.5d_%d_0_%s\n", sceneIdx, rotateIdx, filenameAppend, sceneIdx, rotateIdx, filenameAppend);
            }
        }

        fclose(fp_csv);
    }

    fclose(fp_imageList);
    fclose(fp_imageCopyBatch);

    exit(0);
}

struct VerifyImae{
    bool testImage { false };
    int answer{ 0 };
};

#if 1
void GenerateBanUserList()
{
    std::unordered_map<std::string, VerifyImae> verifyImageList;

    FILE* fp_banUserList = fopen("../final_images/crowdflower/banUserList.txt", "w");

    // loop csv file
    for (size_t i = 0; i < NUM_CSV_FILE; i++)
    {
        char searchPath[256];
        sprintf_s(searchPath, sizeof(searchPath), "../final_images/crowdflower/judgement%.3d.csv", i);

        std::ifstream ifs(searchPath);

        if (!ifs) {
            printf("Cannot open file [%s]", searchPath);
            continue;
        }

        const int MAX_CHARS = 8192;  // Alloc enough size.
        std::vector<char> buf(MAX_CHARS);

        char curUserName[256] = "kinuwaki";
        const float passRatio = 0.8f;
        int lod8Question = 0;
        int lod8Correctness = 0;

        while (ifs.peek() != -1) {
            ifs.getline(&buf[0], MAX_CHARS);
            std::string linebuf(&buf[0]);

            // Skip if empty line.
            if (linebuf.empty()) {
                continue;
            }

            char* token = (char*)(linebuf.c_str());

            // Skip if first line.
            if ((0 == strncmp(token, "WorkerID", 6))) {
                continue;
            }

            char userName[256], filename[256];
            int dummy[2];
            int LOD;
            int badAnswer;

            char *s = strtok(token, ",");
            sscanf_s(s, "%s\n", &userName);
            s = strtok(NULL, ",");
            sscanf_s(s, "%d\n", &dummy[0]);
            s = strtok(NULL, ",");
            sscanf_s(s, "%d\n", &dummy[1]);
            s = strtok(NULL, ",");
            sscanf_s(s, "%d\n", &LOD);
            s = strtok(NULL, ",");
            sscanf_s(s, "%d\n", &badAnswer);
            s = strtok(NULL, ",");
            sscanf_s(s, "%s\n", filename, sizeof(filename));

            if (strcmp(userName, curUserName) != 0)
            {

                if (lod8Question < 10)
                {
                    fprintf(fp_banUserList, "%s\n", curUserName);
                } 
                else
                {
                    if (lod8Correctness / (float)lod8Question < passRatio)
                    {
                        fprintf(fp_banUserList, "%s\n", curUserName);
                    }
                    else
                    {
                        printf("passed\n");
                    }
                }
                lod8Question = lod8Correctness = 0;
                strcpy(curUserName, userName);
            }

            if (LOD == 8)
            {
                lod8Question++;
                if (badAnswer == 0)
                {
                    lod8Correctness++;
                }
            }

        }
    }
    fclose(fp_banUserList);
    exit(0);
}
#else
void GenerateBanUserList()
{
    std::unordered_map<std::string, VerifyImae> verifyImageList;

    // scan image list
    {
        char searchPath[256];
        sprintf_s(searchPath, sizeof(searchPath), "../final_images/crowdflower/ban/imageListForBan.txt");
        FILE* fp = fopen(searchPath, "r");
        if (fp == NULL)
            exit(0);

        char filename[256];
        int answer;
        
        for (size_t i = 0; i < NUM_VERIFY_IMAGE * 2; i++)
        {
            fscanf(fp, "%s %d\n", filename, &answer);

            verifyImageList[filename].testImage = true;
            verifyImageList[filename].answer = answer;
        }

        fclose(fp);
    }

    FILE* fp_banUserList = fopen("../final_images/crowdflower/ban/banUserList.txt", "w");

    // loop csv file
    for (size_t i = 0; i < NUM_CSV_FILE; i++)
    {
        char searchPath[256];
        sprintf_s(searchPath, sizeof(searchPath), "../final_images/crowdflower/judgement%.3d.csv", i);

        std::ifstream ifs(searchPath);

        if (!ifs) {
            printf("Cannot open file [%s]", searchPath);
            continue;
        }

        const int MAX_CHARS = 8192;  // Alloc enough size.
        std::vector<char> buf(MAX_CHARS);

        char curUserName[256] = "kinuwaki";
        const float passRatio = 0.7f;
        float numberCorrection = 0.0f;
        float answerCounter = 0.0f;

        while (ifs.peek() != -1) {
            ifs.getline(&buf[0], MAX_CHARS);
            std::string linebuf(&buf[0]);

            // Skip if empty line.
            if (linebuf.empty()) {
                continue;
            }

            char* token = (char*)(linebuf.c_str());

            // Skip if first line.
            if ((0 == strncmp(token, "WorkerID", 6))) {
                continue;
            }

            char userName[256], filename[256];
            int dummy[3];
            char YesOrNo[16];

            char *s = strtok(token, ",");
            sscanf_s(s, "%s\n", &userName);
            s = strtok(NULL, ",");
            sscanf_s(s, "%d\n", &dummy[0]);
            s = strtok(NULL, ",");
            sscanf_s(s, "%d\n", &dummy[1]);
            s = strtok(NULL, ",");
            sscanf_s(s, "%d\n", &dummy[2]);
            s = strtok(NULL, ",");
            sscanf_s(s, "%s\n", YesOrNo, sizeof(YesOrNo));
            s = strtok(NULL, ",");
            sscanf_s(s, "%s\n", filename, sizeof(filename));

            if (strcmp(userName, curUserName) != 0)
            {
                if (answerCounter != 0)
                {
                    if ((numberCorrection  / static_cast<float>(answerCounter)) < passRatio)
                    {
                        fprintf(fp_banUserList, "%s\n", curUserName);
                    }

                }
                strcpy(curUserName, userName);
                answerCounter = numberCorrection = 0;
            }

            if (verifyImageList[filename].testImage == true)
            {
                if (strcmp(YesOrNo, "Yes"))
                {
                    if (verifyImageList[filename].answer == 1)
                        numberCorrection += 1.0f;
                    answerCounter += 1.0f;
                }
                else if(strcmp(YesOrNo, "No"))
                {
                    if (verifyImageList[filename].answer == 0)
                        numberCorrection += 1.5f;
                    answerCounter += 1.5f;
                }
                else
                {
                    int tmp;
                    printf("unknown case");
                    scanf("%d", &tmp);
                }
            }
        }
    }
    fclose(fp_banUserList);
    exit(0);
}
#endif

void main(int argc, char* argv[])
{
#if 0
    ImageDistributerForCrowdFlower();
#elif 0
    if (argc != 3)
    {
        printf("clasffier.exe path object_name");
        exit(0);
    }

    char* path = argv[1];
    char* objectname = argv[2];

    const int NUM_RATIO = 10;
    char filename[512];

    int ratio[NUM_RATIO] = { 3, 6, 12, 25, 40, 55, 70, 85, 99, 100 };
    for (size_t i = 0; i < NUM_RATIO; i++)
    {
        sprintf(filename, "%s_%.3d.obj", objectname, ratio[i]);
        CleanupObj(path, filename);
    }
#else
    AnalyzeCsvFile();
//    DumpImageListForBan();
//    GenerateBanUserList();
#endif
}