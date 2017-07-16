//
// Created by bian on 2017/7/15.
//

#ifndef PPTD_CONFIG_H
#define PPTD_CONFIG_H

#define row_count 1000
#define trajectory_item_num 20  // 每一行的轨迹个数最大为20个
#define movePointLen 3      // 移动点字符串的长度(2+1) '\0'
#define disease_len 50
#define DB_FILE_PATH_3 "../config/database.txt"
#define BIG_DB_FILE_PATH "../config/database_test.txt"
#define Set_Max_Size 100
#define String_Max_Len 10
#define Subset_Max_Length 20    // 叶子结点的最大数目
#define childListsLength 5      // 子节点最大数目（根据论文中的树！！！Pul下面的子树数目是有很大影响的）
#define treeHeight 3    // 树的高度
#define CONFIG_PATH "../config/sensitive_tree.txt"
#define MAX_TEXT_LEN 100
#define QUEUE_LEN 28        // 广度优先遍历队列最大长度


#endif //PPTD_CONFIG_H
