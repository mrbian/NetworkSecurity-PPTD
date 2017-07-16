#include <stdio.h>
#include "Tree/tree.h"
#include "Database/database.h"
#include "SAGTD/common/common.h"
#include "SAGTD/STR/str.h"
#include "SAGTD/SAGTD.h"
#include "MPSTD/MPSTD.h"
#include "Print/sagtd_print.h"
#include "Print/mpstd_print.h"
#include "config/config.h"
#include "Analysis/analysis.h"
#include "Print/main_print.h"

//#define ¦Ä 2
//#define ¦Ò 0.5

int main()
{
    analysis_main();

//    system("color f0");
//    database * originDB = initDb();
//    migrate(originDB,DB_FILE_PATH_3);     // originDB
//
//    // DB
//    database * db = initDb();
//    migrate(db,DB_FILE_PATH_3);
//
//    // tree
//    treeNode * root = migrateTree(CONFIG_PATH);
//
//    main_thread(originDB,root,db);
//    return 0;
}
