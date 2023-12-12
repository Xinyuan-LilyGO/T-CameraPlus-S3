/*
 * @Description: Arduino_Explorer.cpp
 * @version: V1.0.0
 * @Author: Xk_w
 * @Date: 2023-10-05 08:44:18
 * @LastEditors: Xk_w
 * @LastEditTime: 2023-11-22 15:17:38
 * @License: GPL 3.0
 */
#include "Arduino_Explorer.h"

Arduino_Explorer::Arduino_Explorer()
{
}

// void Arduino_Explorer::begin(SPIClass spi, fs::SDFS sd)
// {
//     _spi = &spi;
//     _sd = &sd;
// }

bool Arduino_Explorer::File_Directory_Refresh(fs::FS *fs, std::vector<String> directory_name,
                                              std::vector<String> *folder_name, std::vector<File_Manager> *file_manager)
{
    File_Manager file_manager_temp; // 文件结构体暂存器
    String target_directory;        // 执行目录操作的目标路径
    for (int i = 0; i < directory_name.size(); i++)
    {
        if (directory_name[i] == "/") // 判断尾部是否有文件页操作符号
        {
            target_directory = directory_name[i];
        }
        else
        {
            target_directory = target_directory + "/" + directory_name[i];
        }
    }

    // log_d("Target directory: %s\n", directory_name.back());
    // log_d("Target directory: %s\n", target_directory);
    // Serial.printf("Target directory: %s\n", target_directory);
    // Serial.print("Target directory: ");
    // Serial.println(target_directory);
    // Serial.println();

    File root = fs->open(target_directory); // fs打开目标目录
    if (!root)
    {
        log_w("Failed to open directory");
        return false;
    }
    if (!root.isDirectory())
    {
        log_w("Not a directory");
        return false;
    }

    File file = root.openNextFile(); // 开始打开目标目录下的下一个文件
    while (file)                     // 判断是否有文件
    {
        if (file.isDirectory()) // 判断是否是文件夹
        {
            log_v("  Folder: ");
            log_v("%s", file.name());
            folder_name->push_back(file.name());
        }
        else
        {
            log_v("  File: ");
            log_v("%s", file.name());
            log_v("   ");
            log_v("%d Kb", file.size());
            file_manager_temp.file_name = file.name();
            file_manager_temp.file_size = file.size();
            file_manager->push_back(file_manager_temp);
        }
        file = root.openNextFile(); // 循环打开目标目录下的下一个文件
    }
    return true;
}

void Arduino_Explorer::File_Directory_Sort(unsigned char sort_method, std::vector<String> *folder_name,
                                           std::vector<File_Manager> *file_manager)
{
    switch (sort_method)
    {
    case File_Manager_Sort_Order:
        sort(folder_name->begin(), folder_name->end()); // 顺序
        sort(file_manager->begin(), file_manager->end(),
             [](File_Manager a, File_Manager b)
             { return a.file_name >= b.file_name; });
        break;
    case File_Manager_Sort_Reverse:
        reverse(folder_name->begin(), folder_name->end()); // 倒序
        sort(file_manager->begin(), file_manager->end(),
             [](File_Manager a, File_Manager b)
             { return a.file_name <= b.file_name; });
        break;

    default:
        break;
    }
}

bool Arduino_Explorer::Arduino_Explorer::File_Directory_Suffix_Scan(fs::FS *fs, std::vector<String> directory_name,
                                                                    String Suffix, std::vector<File_Manager> *file_manager)
{
    File_Manager file_manager_temp; // 文件结构体暂存器
    String target_directory;        // 执行目录操作的目标路径
    for (int i = 0; i < directory_name.size(); i++)
    {
        if (directory_name[i] == "/") // 判断尾部是否有文件页操作符号
        {
            target_directory = directory_name[i];
        }
        else
        {
            target_directory = target_directory + "/" + directory_name[i];
        }
    }

    // log_d("Target directory: %s\n", directory_name.back());
    // log_d("Target directory: %s\n", target_directory);
    // Serial.printf("Target directory: %s\n", target_directory);
    // Serial.print("Target directory: ");
    // Serial.println(target_directory);
    // Serial.println();

    File root = fs->open(target_directory); // fs打开目标目录
    if (!root)
    {
        log_w("Failed to open directory");
        return false;
    }
    if (!root.isDirectory())
    {
        log_w("Not a directory");
        return false;
    }

    File file = root.openNextFile(); // 开始打开目标目录下的下一个文件
    while (file)                     // 判断是否有文件
    {
        if (file.isDirectory()) // 判断是否是文件夹
        {
            // log_v("  Folder: ");
            // log_v("%s", file.name());
        }
        else
        {
            if (strcasestr(file.name(), Suffix.c_str()) != NULL)
            {
                log_v("  File: ");
                log_v("%s", file.name());
                log_v("   ");
                log_v("%d Kb", file.size());
                file_manager_temp.file_name = file.name();
                file_manager_temp.file_size = file.size();
                file_manager->push_back(file_manager_temp);
            }
        }
        file = root.openNextFile(); // 循环打开目标目录下的下一个文件
    }
    return true;
}

Arduino_Explorer::~Arduino_Explorer()
{
}
