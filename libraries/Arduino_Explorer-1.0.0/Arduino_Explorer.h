/*
 * @Description(CN):基于Arduino的文件管理系统
 * @version: V1.0.0
 * @Author: Xk_w
 * @Date: 2023-10-05 08:45:32
 * @LastEditors: Xk_w
 * @LastEditTime: 2023-11-22 15:17:20
 * @License: GPL 3.0
 */
#pragma once

#include <iostream>
#include <vector>
#include <FS.h>

class Arduino_Explorer
{
public:
    Arduino_Explorer();

    enum File_Manager_Sort
    {
        File_Manager_Sort_Order = 0,
        File_Manager_Sort_Reverse
    };

    struct File_Manager
    {
        String file_name;
        size_t file_size;
    };

    // void begin(SPIClass spi, SDFS sd);

    /**
     * @brief 文件刷新函数
     * @param *fs:指向SD文件的指针
     * @param directory_name:当前目录下的目录容器名
     * @param *folder_name:填写当前目录下的文件夹的名字
     * @param *file_manager:填写当前目录下的文件的名字和所占内存大小（kb）
     * @return 0 or 1
     * @Date 2023-10-05 11:03:22
     */
    bool File_Directory_Refresh(fs::FS *fs, std::vector<String> directory_name,
                                std::vector<String> *folder_name, std::vector<File_Manager> *file_manager);

    /**
     * @brief 文件排序函数
     * @param sort_method:文件排序的模式（从小到大、从大到小）
     * @param *folder_name:填写当前目录下的文件夹的名字
     * @param *file_manager:填写当前目录下的文件的名字和所占内存大小（kb）
     * @return
     * @Date 2023-10-05 11:13:51
     */
    void File_Directory_Sort(unsigned char sort_method, std::vector<String> *folder_name,
                             std::vector<File_Manager> *file_manager);

    /**
     * @brief 扫描文件后缀函数并获取函数
     * @param *fs:指向SD文件的指针
     * @param directory_name:当前目录下的目录容器名
     * @param *folder_name:填写当前目录下的文件夹的名字
     * @param *file_manager:填写当前目录下的文件的名字和所占内存大小（kb）
     * @return 0 or 1
     * @Date 2023-10-05 11:03:22
     */
    bool File_Directory_Suffix_Scan(fs::FS *fs, std::vector<String> directory_name,
                                    String Suffix, std::vector<File_Manager> *file_manager);

    ~Arduino_Explorer();

protected:
    // SPIClass *_spi;
    // SDFS *_sd;

private:
};