//
// Created by zlysm on 2022/9/6.
//

#ifndef DSA_BINNODE_TRAVPREORDER_H
#define DSA_BINNODE_TRAVPREORDER_H

template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST &visit) { //��������������㷨ͳһ���
    switch (rand() % 3) { //�˴������ѡ���������ԣ�������ѡ��
        case 1:
            travPre_I1(this, visit);
            break; //������#1
        case 2:
            travPre_I2(this, visit);
            break; //������#2
        default:
            travPre_R(this, visit);
            break; //�ݹ��
    }
}

#endif //DSA_BINNODE_TRAVPREORDER_H
