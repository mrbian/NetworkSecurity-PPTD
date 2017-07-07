#include <stdio.h>
#include "LinkedList/LinkedList.h"
#include "BinaryTreeNode/BinaryTreeNode.h"
#include "Queue/queue.h"
#include "Tree/tree.h"
#include "Database/database.h"
#include "SAGTD/common/common.h"
#include "SAGTD/STR/str.h"
#include "SAGTD/SAGTD.h"
#include "MPSTD/MPSTD.h"

//#define δ 2
//#define σ 0.5

void _main_test(){
    //    _t_linkedlist_main();
//    _t_tree_main();
//    _t_queue_main();
//    _tree_main();
//    _db_main();
//    _common_main(originDB);
//    _str_test();
//    trackSet * AResult = str_main(2);
//    traverseSet(AResult,printSet);
//    database * db = initDb();
//    migrate(db,Db_Config_Path);
}

int main()
{
//    _main_test();
    // DB
    database * originDB = initDb();
    migrate(originDB,DB_FILE_PATH_3);     // originDB
    printf("the origin db is\n");
    traverseDb(originDB,printRow);
    printf("\n");

    // tree
    treeNode * root = migrateTree(CONFIG_PATH);

    float Pb = 0.5;
    // STR
    trackSet * A = str_main(originDB,maxDepth);

    // SAGTD
    database * Ts = SAGTD(originDB,root, maxDepth ,Pb);
    sortDB(Ts);
    printf("After SAGTD the result is \n");
    traverseDb(Ts,printRow);
    printf("\n");


    // MPSTD
    database * Tg = mpstd(originDB,root,Ts,A,Pb);
    sortDB(Tg);
    printf("After MPSTD the result is \n");
    traverseDb(Tg,printRow);
    printf("\n");

    return 0;
}
