//
// Created by bian on 2017/7/8.
//

#ifndef PPTD_SAGTD_PRINT_H
#define PPTD_SAGTD_PRINT_H
#include "../SAGTD/SAGTD.h"
#include "../MPSTD/MPSTD.h"

// SAGTD�𲽴�ӡ����
int SAGTDBreakFunc(database * Bj, database *Cj,  database * T, float PbThreshold, int maxDepth, trackRow * attack_row);

// SAGTD���𲽴�ӡ����
int SAGTDNonBreakFunc(database * Bj, database *Cj,  database * T, float PbThreshold, int maxDepth, trackRow * attack_row);

// �õ��û�ѡ��
int SAGTDChoice();

// SAGTD�㷨��ʾ������
database * SAGTDFunc(database * originDB,treeNode * root,database * db, int maxDepth, float PbThreshold);

#endif //PPTD_SAGTD_PRINT_H
