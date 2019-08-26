/*****************************************************************************************************************************
This project was supported by the National Basic Research 973 Program of China under Grant No.2011CB302301
Huazhong University of Science and Technology (HUST)   Wuhan National Laboratory for Optoelectronics

FileName�G initialize.h
Author: Hu Yang		Version: 2.1	Date:2011/12/02
Description: 

History:
<contributor>     <time>        <version>       <desc>                   <e-mail>
Yang Hu	        2009/09/25	      1.0		    Creat SSDsim       yanghu@foxmail.com
                2010/05/01        2.x           Change 
Zhiming Zhu     2011/07/01        2.0           Change               812839842@qq.com
Shuangwu Zhang  2011/11/01        2.1           Change               820876427@qq.com
Chao Ren        2011/07/01        2.0           Change               529517386@qq.com
Hao Luo         2011/01/01        2.0           Change               luohao135680@gmail.com
*****************************************************************************************************************************/
#ifndef INITIALIZE_H
#define INITIALIZE_H 10000

#include "avlTree.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

// Narges
#define UMASS
// end NARGES

#define SECTOR 512
#define BUFSIZE 200

#define DYNAMIC_ALLOCATION 0
#define STATIC_ALLOCATION 1

#define INTERLEAVE 0
#define TWO_PLANE 1

#define NORMAL 2
#define INTERLEAVE_TWO_PLANE 3
#define COPY_BACK 4

#define AD_RANDOM 1
#define AD_COPYBACK 2
#define AD_TWOPLANE 4
#define AD_INTERLEAVE 8
#define AD_TWOPLANE_READ 16

#define READ 1
#define WRITE 0

#define CHANNEL_IDLE 000
#define CHANNEL_C_A_TRANSFER 3
#define CHANNEL_GC 4
#define CHANNEL_DATA_TRANSFER 7
#define CHANNEL_TRANSFER 8
#define CHANNEL_UNKNOWN 9

#define CHIP_IDLE 100
#define CHIP_WRITE_BUSY 101
#define CHIP_READ_BUSY 102
#define CHIP_C_A_TRANSFER 103
#define CHIP_DATA_TRANSFER 107
#define CHIP_WAIT 108
#define CHIP_ERASE_BUSY 109
#define CHIP_COPYBACK_BUSY 110
#define UNKNOWN 111

#define SR_WAIT 200
#define SR_R_C_A_TRANSFER 201
#define SR_R_READ 202
#define SR_R_DATA_TRANSFER 203
#define SR_W_C_A_TRANSFER 204
#define SR_W_DATA_TRANSFER 205
#define SR_W_TRANSFER 206
#define SR_COMPLETE 299

#define REQUEST_IN 300
#define OUTPUT 301

#define GC_WAIT 400
#define GC_ERASE_C_A 401
#define GC_COPY_BACK 402
#define GC_COMPLETE 403
#define GC_INTERRUPT 0
#define GC_UNINTERRUPT 1

//#define CHANNEL(lsn) (lsn&0x0000)>>16
//#define chip(lsn) (lsn&0x0000)>>16
//#define die(lsn) (lsn&0x0000)>>16
//#define PLANE(lsn) (lsn&0x0000)>>16
//#define BLOKC(lsn) (lsn&0x0000)>>16
//#define PAGE(lsn) (lsn&0x0000)>>16
//#define SUBPAGE(lsn) (lsn&0x0000)>>16

#define PG_SUB 0xffffffff

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define ERROR -1
#define INFEASIBLE -2
//#define OVERFLOW	-3
typedef int Status;

struct ac_time_characteristics {
    int tPROG; //program time
    int tDBSY; //bummy busy time for two-plane program
    int tBERS; //block erase time
    int tCLS; //CLE setup time
    int tCLH; //CLE hold time
    int tCS; //CE setup time
    int tCH; //CE hold time
    int tWP; //WE pulse width
    int tALS; //ALE setup time
    int tALH; //ALE hold time
    int tDS; //data setup time
    int tDH; //data hold time
    int tWC; //write cycle time
    int tWH; //WE high hold time
    int tADL; //address to data loading time
    int tR; //data transfer from cell to register
    int tAR; //ALE to RE delay
    int tCLR; //CLE to RE delay
    int tRR; //ready to RE low
    int tRP; //RE pulse width
    int tWB; //WE high to busy
    int tRC; //read cycle time
    int tREA; //RE access time
    int tCEA; //CE access time
    int tRHZ; //RE high to output hi-z
    int tCHZ; //CE high to output hi-z
    int tRHOH; //RE high to output hold
    int tRLOH; //RE low to output hold
    int tCOH; //CE high to output hold
    int tREH; //RE high to output time
    int tIR; //output hi-z to RE low
    int tRHW; //RE high to WE low
    int tWHR; //WE high to RE low
    int tRST; //device resetting time
} ac_timing;

struct ssd_info {
    double ssd_energy; //SSD����ӡA�O�ɶ��M����ƪ����,��Ӧ]�l
    int time_scale;
    //int64_t current_time; //�O���Y�ήɶ�
    //int64_t next_request_time;
    unsigned long long current_time; //�O���Y�ήɶ�
    unsigned long long next_request_time;
    unsigned int real_time_subreq; //�O����ɪ��g�ШD�ӼơA�Φb���ʺA���t�ɡAchannel�u�������p
    int flag;
    int active_flag; //�O���D�ʼg�O�_����A�p�G�o�{�W��A�ݭn�N�ɶ��Q�e���i,0�����N������A1���ܳQ����A�ݭn�Q�e���i�ɶ�
    unsigned int page;

    unsigned int token; //�b�ʺA���t���A������C�����t�b�Ĥ@��channel�ݭn�����@�ӥO�P�A�C���q�O�P�ҫ�����m�}�l���t
    unsigned int gc_request; //�O���bSSD���A���e�ɨ観�h��gc�ާ@���ШD

    unsigned int read_request_size;
    unsigned int write_request_size;

    unsigned int write_request_count; //�O���g�ާ@������
    unsigned int read_request_count; //�O��Ū�ާ@������
    int64_t write_avg; //�O���Ω�p��g�ШD�����T���ɶ����ɶ�
    int64_t read_avg; //�O���Ω�p��Ū�ШD�����T���ɶ����ɶ�

    //unsigned int min_lsn;
    //unsigned int max_lsn;
    int64_t min_lsn, max_lsn;
    unsigned long read_count;
    unsigned long program_count;
    unsigned long erase_count;
    unsigned long direct_erase_count;
    unsigned long copy_back_count;
    unsigned long m_plane_read_count;
    unsigned long m_plane_prog_count;
    unsigned long interleave_count;
    unsigned long interleave_read_count;
    unsigned long inter_mplane_count;
    unsigned long inter_mplane_prog_count;
    unsigned long interleave_erase_count;
    unsigned long mplane_erase_conut;
    unsigned long interleave_mplane_erase_count;
    unsigned long gc_copy_back;
    unsigned long write_flash_count; //���?�ͪ���flash���g�ާ@
    unsigned long waste_page_count; //�O���]�����ũR�O�����s�ɽo�������O
    float ave_read_size;
    float ave_write_size;
    unsigned int request_queue_length;
    unsigned int update_read_count; //�O���]����s�ާ@�ɽo���B�~Ū�X�ާ@

    char parameterfilename[30];
    char tracefilename[30];
    char outputfilename[30];
    char statisticfilename[30];
    char statisticfilename2[30];

    FILE *outputfile;
    FILE *tracefile;
    FILE *statisticfile;
    FILE *statisticfile2;

    struct parameter_value *parameter; //SSD�ѼƦ]�l
    struct dram_info *dram;
    struct request *request_queue; //dynamic request queue
    struct request *request_tail; // the tail of the request queue
    struct sub_request *subs_w_head; //���ĥΥ��ʺA���t�ɡA���t�O�����D���ӱ�������channel�W�A�ҥH�����bssd�W�A���i�Jprocess��Ʈɤ~���������channel��Ū�ШD���C�W
    struct sub_request *subs_w_tail;
    struct event_node *event; //�ƥ󶤦C�A�C���ͤ@�ӷs���ƥ�A���Ӯɶ����ǥ[��o�Ӷ��C�A�bsimulate��Ƴ̫�A�ھڳo�Ӷ��C�������ɶ��A�T�w�ɶ�
    struct channel_info *channel_head; //���Qchannel���c��Ʋժ����a�}
};

struct channel_info {
    int chip; //���ܦb���`�u�W���h������
    unsigned long read_count;
    unsigned long program_count;
    unsigned long erase_count;
    unsigned int token; //�b�ʺA���t���A������C�����t�b�Ĥ@��chip�ݭn�����@�ӥO�P�A�C���q�O�P�ҫ�����m�}�l���t

    int current_state; //channel has serveral states, including idle, command/address transfer,data transfer,unknown
    int next_state;
    int64_t current_time; //�O���ӳq�D�����e�ɶ�
    int64_t next_state_predict_time; //the predict time of next state, used to decide the sate at the moment

    struct event_node *event;
    struct sub_request *subs_r_head; //channel�W��Ū�ШD���C�Y�A���A�ȳB�󶤦C�Y���l�ШD
    struct sub_request *subs_r_tail; //channel�W��Ū�ШD���C���A�s�[�i�Ӫ��l�ШD�[�춤��
    struct sub_request *subs_w_head; //channel�W���g�ШD���C�Y�A���A�ȳB�󶤦C�Y���l�ШD
    struct sub_request *subs_w_tail; //channel�W���g�ШD���C�A�s�[�i�Ӫ��l�ШD�[�춤��
    struct gc_operation *gc_command; //�O���ݭn?��gc����m
    struct chip_info *chip_head;
};

struct chip_info {
    unsigned int die_num; //���ܤ@�����ɤ����h�֭�die
    unsigned int plane_num_die; //indicate how many planes in a die
    unsigned int block_num_plane; //indicate how many blocks in a plane
    unsigned int page_num_block; //indicate how many pages in a block
    unsigned int subpage_num_page; //indicate how many subpage in a page
    unsigned int ers_limit; //��chip���C������Q����������
    unsigned int token;

    int current_state; //channel has serveral states, including idle, command/address transfer,data transfer,unknown
    int next_state;
    int64_t current_time; //�O���ӳq�D�����e�ɶ�
    int64_t next_state_predict_time; //the predict time of next state, used to decide the sate at the moment

    unsigned long read_count; //how many read count in the process of workload
    unsigned long program_count;
    unsigned long erase_count;

    struct ac_time_characteristics ac_timing;
    struct die_info *die_head;
};

struct die_info {

    unsigned int token; //�b�ʺA���t���A������C�����t�b�Ĥ@��plane�ݭn�����@�ӥO�P�A�C���q�O�P�ҫ�����m�}�l���t
    struct plane_info *plane_head;
};

struct plane_info {
    int add_reg_ppn; //read�Awrite�ɧ�a�}�ǰe����ܶq�A���ܶq�N���a�}�H�s���Cdie��busy�ܬ�idle�ɡA�M���a�} //���i��]���@��h���M�g�A�b�@��Ū�ШD�ɡA���h�ӬۦP��lpn�A�ҥH�ݭn��ppn�ӰϤ�
    unsigned int free_page; //��plane�����h��free page
    unsigned int ers_invalid; //�O����plane���������Ī�����
    unsigned int active_block; //if a die has a active block, �Ӷ����ܨ䪫�z����
    int can_erase_block; //�O���b�@��plane���ǳƦbgc�ާ@���Q�����ާ@����,-1�������N�����X�A����
    struct direct_erase *erase_node; //�ΨӰO���i�H�����R��������,�b����s��ppn�ɡA�C���X�{invalid_page_num==64�ɡA�N��K�[��o�ӫ��w�W�A��GC�ާ@�ɪ����R��
    struct blk_info *blk_head;
};

struct blk_info {
    unsigned int erase_count; //块的擦除次数，该项记录在ram中，用于GC
    unsigned int free_page_num; //记录该块中的free页个数，同上
    unsigned int invalid_page_num; //记录该块中失效页的个数，同上
    int last_write_page; //记录最近一次写操作执行的页数,-1表示该块没有一页被写过
    struct page_info *page_head; //记录每一子页的状态
};

struct page_info { //lpn�O���Ӫ��z���s�x���޿譶�A�����޿譶���ĮɡAvalid_state�j��0�Afree_state�j��0�F
    int valid_state; //indicate the page is valid or invalid
    int free_state; //each bit indicates the subpage is free or occupted. 1 indicates that the bit is free and 0 indicates that the bit is used
    unsigned int lpn;
    unsigned int written_count; //�O���ӭ��Q�g������
};

struct dram_info {
    unsigned int dram_capacity;
    int64_t current_time;

    struct dram_parameter *dram_paramters;
    struct map_info *map;
    struct buffer_info *buffer;
};

/*********************************************************************************************
*management of buffer pages have been written back: in buffer_info maintaining a queue:written. This queue has a team first, team tail
*everytime buffer management in,When the request is hit, the group̼ first team to move to the LRU, but look at this group if there has been 
*written lsn, yes, you need to move to this group while the tail written queue. This increase and reduction method of the queue
*as follows: when the need to delete the writeback lsn to make room for a new write request to find out you can remove the lsn in written first in the team. 
*When you need to add a new writtenback lsn, can be written back to the page to find the meaning of this group is added to the queue pointer written_insert written
*before nodes. We need to maintain a pointer to the buffer of the LRU queue oldest one point to write back a page, the next time you want to write back
*just by this pointer before returning to a group retreated to write back 


**********************************************************************************************/
typedef struct buffer_group {
    TREE_NODE node; //Tree nodes must be placed in front of a user-defined structure, pay attention!
    struct buffer_group *LRU_link_next; // next node in LRU list
    struct buffer_group *LRU_link_pre; // previous node in LRU list

    unsigned int group; //the first data logic sector number of a group stored in buffer
    unsigned int stored; //indicate the sector is stored in buffer or not. 1 indicates the sector is stored and 0 indicate the sector isn't stored.
        //EX.  00110011 indicates the first, second, fifth, sixth sector is stored in buffer.
    unsigned int dirty_clean; //it is flag of the data has been modified, one bit indicates one subpage. EX. 0001 indicates the first subpage is dirty
    int flag; //indicates if this node is the last 20% of the LRU list
} buf_node;

struct dram_parameter {
    float active_current;
    float sleep_current;
    float voltage;
    int clock_time;
};

struct map_info {
    struct entry *map_entry; //�Ӷ��O�M�g�����c����w,each entry indicate a mapping information
    struct buffer_info *attach_info; // info about attach map
};

struct controller_info {
    unsigned int frequency; //���ܸӱ��s�����u�@�W�v
    int64_t clock_time; //���ܤ@�Ӯ���P�����ɶ�
    float power; //���ܱ��s�����ɶ������
};

struct request {
    unsigned long long int time; //�ШD��F���ɶ��A��쬰us,�o�ةM�q�`���ߺD���@�ˡA�q�`���Oms�����A�o�ػݭn���ӳ���ܴ��L�{
    unsigned int lsn; //�ШD���_�l�a�}�A�޿�a�}
    unsigned int size; //�ШD���j�p�A�J�h�֭Ӯ���
    unsigned int operation; //�ШD�������A1��Ū�A0���g

    unsigned int *need_distr_flag;
    unsigned int complete_lsn_count; //record the count of lsn served by buffer

    int distri_flag; // indicate whether this request has been distributed already

    int64_t begin_time;
    int64_t wait_time;
    int64_t response_time;
    double energy_consumption; //�O���ӽШD����q���ӡA��쬰uJ

    struct sub_request *subs; //�챵���ݩ�ӽШD���Ҧ��l�ШD
    struct request *next_node; //���Q�U�@�ӽШD���c��
};

struct sub_request {
    unsigned int lpn; //�o�ؿ��ܸӤl�ШD���޿譶��
    unsigned int ppn; //���t���Ӫ��z�l�����o�Ӥl�ШD�C�bmulti_chip_page_mapping���A?�ͤl���ШD�ɥi��N���Dpsn���ȡA��L�ɭ�psn���ȥ�page_map_read,page_map_write��FTL�̩��h���?�͡C
    unsigned int operation; //���ܸӤl�ШD�������A���FŪ1 �g0�A�٦������Atwo plane���ާ@
    int size;

    unsigned int current_state; //���ܸӤl�ШD�ҳB�����A�A�����w�qsub request
    int64_t current_time;
    unsigned int next_state;
    int64_t next_state_predict_time;
    unsigned int state; //�ϥ�state���̰�����ܸӤl�ШD�O�_�O�@��h�M�g���Y�����@�ӡA�O���ܡA�ݭnŪ��buffer���C1���ܬO�@��h�A0���ܤ��μg��buffer
        //Ū�ШD���ݭn�o�Ӧ����Alsn�[size�N�i�H����X�ӭ������A;���O�g�ШD�ݭn�o�Ӧ����A�j�����g�l�ШD�Ӧ۩�buffer�g�^�ާ@�A�i�঳�����l�����s�򪺱��p�A�ҥH�ݭn��W�����Ӧ���

    int64_t begin_time; //�l�ШD�}�l�ɶ�
    int64_t wait_time;
    int64_t complete_time; //�O���Ӥl�ШD���B�z�ɶ�,�J�u���g�J�Ϊ�Ū�X�ƾڪ��ɶ�

    struct local *location; //�b�R�A���t�M�V�X���t�覡���A�w��lpn�N���D��lpn�Ӥ��t�쨺��channel�Achip�Adie�Aplane�A�o�ӵ��c��ΨӫO�s�p��o�쪺�a�}
    struct sub_request *next_subs; //���Q�ݩ�P�@��request���l�ШD
    struct sub_request *next_node; //���Q�P�@��channel���U�@�Ӥl�ШD���c��
    struct sub_request *update; //�]���b�g�ާ@���s�b��s�ާ@�A�]���b�ʺA���t�覡���L�k�ϥ�copyback�ާ@�A�ݭn�N��Ӫ���Ū�X��~��i��g�ާ@�A�ҥH�A�N�]��s?�ͪ�Ū�ާ@���b�o�ӫ��w�W
};

/***********************************************************************
*�ƥ�`�I���s�ɶ����W���A�C���ɶ����W�[�O�ھڮɶ��̪񪺤@�Өƥ�ӽT�w��
************************************************************************/
struct event_node {
    int type; //�O���Өƥ������A1���ܩR�O�����A2���ܼƾڶǿ�����
    int64_t predict_time; //�O���o�Ӯɶ��}�l���w�p�ɶ��A����e����o�Ӯɶ�
    struct event_node *next_node;
    struct event_node *pre_node;
};

struct parameter_value {
    unsigned int chip_num; //�O���@��SSD�����h�֭�����
    unsigned int dram_capacity; //�O��SSD��DRAM capacity
    unsigned int cpu_sdram; //�O���������h��

    unsigned int channel_number; //�O��SSD�����h�֭ӳq�D�A�C�ӳq�D�O��W��bus
    unsigned int chip_channel[100]; //�]�mSSD��channel�ƩM�Cchannel�W���ɪ��ƶq

    unsigned int die_chip;
    unsigned int plane_die;
    unsigned int block_plane;
    unsigned int page_block;
    unsigned int subpage_page;

    unsigned int page_capacity;
    unsigned int subpage_capacity;

    unsigned int ers_limit; //�O���C�Ӷ��i����������
    int address_mapping; //�O���M�g�������A1�Gpage�F2�Gblock�F3�Gfast
    int wear_leveling; // WL��k
    int gc; //�O��gc����
    int clean_in_background; //�M���ާ@�O�_�b�e�O����
    int alloc_pool; //allocation pool �j�p(plane�Adie�Achip�Achannel),�]�N�O�֦�active_block�����
    float overprovide;
    float gc_threshold; //���F��o���H�ȮɡA�}�lGC�ާ@�A�b�D�ʼg�������A�}�lGC�ާ@��i�H�{�ɤ��_GC�ާ@�A�A�ȷs�쪺�ШD�F�b���q�������AGC���i���_

    double operating_current; //NAND FLASH���u�@�q�y���OuA
    double supply_voltage;
    double dram_active_current; //cpu sdram work current   uA
    double dram_standby_current; //cpu sdram work current   uA
    double dram_refresh_current; //cpu sdram work current   uA
    double dram_voltage; //cpu sdram work voltage  V

    int buffer_management; //indicates that there are buffer management or not
    int scheduling_algorithm; //�O���ϥέ��ؽի׺�k�A1:FCFS
    float quick_radio;
    int related_mapping;

    unsigned int time_step;
    unsigned int small_large_write; //the threshould of large write, large write do not occupt buffer, which is written back to flash directly

    int striping; //���ܬO�_�ϥΤFstriping�覡�A0�����N���A1���ܦ�
    int interleaving;
    int pipelining;
    int threshold_fixed_adjust;
    int threshold_value;
    int active_write; //���ܬO�_����D�ʼg�ާ@1,yes;0,no
    float gc_hard_threshold; //���q�������Τ���ӰѼơA�����b�D�ʼg�������A�������o���H�ȮɡAGC�ާ@���i���_
    int allocation_scheme; //�O�����t�覡����ܡA0���ܰʺA���t�A1�����R�A���t
    int static_allocation; //�O���O�����R�A���t�覡�A�pICS09���g�峹�ҭz���Ҧ��R�A���t�覡
    int dynamic_allocation; //�O���ʺA���t���覡
    int advanced_commands;
    int ad_priority; //record the priority between two plane operation and interleave operation
    int ad_priority2; //record the priority of channel-level, 0 indicates that the priority order of channel-level is highest; 1 indicates the contrary
    int greed_CB_ad; //0 don't use copyback advanced commands greedily; 1 use copyback advanced commands greedily
    int greed_MPW_ad; //0 don't use multi-plane write advanced commands greedily; 1 use multi-plane write advanced commands greedily
    int aged; //1���ܻݭn�N�o��SSD�ܦ�aged�A0���ܻݭn�N�o��SSD�O��non-aged
    float aged_ratio;
    int queue_length; //�ШD���C�����׭��s
    int page_level_erase; // 0 �N���S�� 1�i�H��page-level�h��erase
    int initial_valid; // 0 �N���S����lvalid data�bssd�̭�, 1 �h��
    float valid_ratio; // ��lvalid data�����

    struct ac_time_characteristics time_characteristics;
};

/********************************************************
*mapping information,state的最高位表示是否有附加映射关系
*********************************************************/
struct entry {
    unsigned int pn; //物理号，既可以表示物理页号，也可以表示物理子页号，也可以表示物理块号
    int state; //十六进制表示的话是0000-FFFF，每位表示相应的子页是否有效（页映射）。比如在这个页中，0，1号子页有效
};

struct local {
    unsigned int channel;
    unsigned int chip;
    unsigned int die;
    unsigned int plane;
    unsigned int block;
    unsigned int page;
    unsigned int sub_page;
};

struct gc_info {
    int64_t begin_time; //�O���@��plane����ɭԶ}�lgc�ާ@��
    int copy_back_count;
    int erase_count;
    int64_t process_time; //��plane��F�h�֮ɶ��bgc�ާ@�W
    double energy_consumption; //��plane��F�h�֯�q�bgc�ާ@�W
};

struct direct_erase {
    int type; // 0 means block, 1 means page
    unsigned int block;
    struct direct_erase *next_node;
    unsigned int page;
};

/**************************************************************************************
 *��?�ͤ@��GC�ާ@�ɡA�N�o�ӵ��c���b������channel�W�A����channel�Ŷ��ɡA�o�XGC�ާ@�R�O
***************************************************************************************/
struct gc_operation {
    unsigned int chip;
    unsigned int die;
    unsigned int plane;
    unsigned int block; //�ӰѼư��b�i���_��gc��Ƥ��ϥΡ]gc_interrupt�^�A�ΨӰO���w���X�Ӫ��ؼж���
    unsigned int page; //�ӰѼư��b�i���_��gc��Ƥ��ϥΡ]gc_interrupt�^�A�ΨӰO���w�g�������ƾھE��������
    unsigned int state; //�O�����egc�ШD�����A
    unsigned int priority; //�O����gc�ާ@���u���šA1���ܤ��i���_�A0���ܥi���_�]�n�H��?�ͪ�gc�ШD�^
    unsigned int type;
    struct gc_operation *next_node;
};

/*
*add by ninja
*used for map_pre function
*/
typedef struct Dram_write_map {
    unsigned int state;
} Dram_write_map;

struct ssd_info *initiation(struct ssd_info *, char *, char *, char *);
struct parameter_value *load_parameters(char parameter_file[30]);
struct page_info *initialize_page(struct page_info *p_page);
struct blk_info *initialize_block(struct blk_info *p_block, struct parameter_value *parameter);
struct plane_info *initialize_plane(struct plane_info *p_plane, struct parameter_value *parameter);
struct die_info *initialize_die(struct die_info *p_die, struct parameter_value *parameter, long long current_time);
struct chip_info *initialize_chip(struct chip_info *p_chip, struct parameter_value *parameter, long long current_time);
struct ssd_info *initialize_channels(struct ssd_info *ssd);
struct dram_info *initialize_dram(struct ssd_info *ssd);

#endif
