#include<bits/stdc++.h>
using namespace std;
int keysize;//���볤��
int stat[256];//״̬����
// 802.2 SNAP Header should be 1st plaintext byte of WEP packet
int text[] = {0xaa};
int S[256];
int S1[256];
int key[256];
int i,j,jk;
#define  Q pair<pair<int,int>,pair<int,int> >
vector <Q>IVList;
#define xx first
#define yy second
void RecoverWEPkey(){
for (int B=0; B < keysize; B++) {//ö������λ

	// ��ʼ��״̬����
	for (i=0; i < 256; i++) {
		 stat[i]=0;
	}

	for(i=0;i<IVList.size();i++) {
	    Q IVRec=IVList[i];
		 key[0]=IVRec.xx.xx;
		 key[1]=IVRec.xx.yy;
		 key[2]=IVRec.yy.xx;
		//IV������ֵ
        int  encr=IVRec.yy.yy;
        //���ĵĵ�һλ

//		if (key[0] ==  B+3) {

//�ҵ���һ��KEY�ֽڶ�Ӧ��IV

			for (i=0; i<256;i++) {
				S[i]=i;
			}

			// 0 to 3+K[b]
			for (i=0; i< B + 3; i++) {
				j=(j+S[i]+key[i]) % 256;
				int  temp = S[i];
				S[i] = S[j];
				S[j] = temp;
				if (i == 1) {
					S1[0]=S[0];
					S1[1]=S[1];
				}

			}


			int  X=S[1];
			if (X < B + 3) {
				if (X+S[X] ==B + 3) {
                 			if (S[0] !=  S1[0] || S[1] !=S1[1]) {
						//print("Throwaway IV   IV[0]=%d,  IV[1]=%d,   IV[2]=%d\n",IV[0],IV[1],IV[2]);
					}

//���ݰ��ĵ�һ�������ֽ�ΪRC4�㷨�����ĵ�һ���ֽ�
//��LLCͷ�ĵ�һ���ֽڣ�0xaa�����ܣ������������Ľ��
                    int  S3Calc = encr ^ text[0];//�õ�RC4�㷨�����ĵ�һ���ֽ�
					int  leaker = S3Calc-j-S[i] %256;//
					stat[leaker]++;
				}
			}




//}
}
	int  max=0;
	int winner=0;
	for(int i=0;i<256;i++){
	if(stat[i]>max){
	max=stat[i];
	winner=i;
	}
	}
printf("%c ",(char)winner);
}
}
Q a;
void IV_read()
{
    printf("this is IV dictionary build part.\n");
    FILE* fp=fopen("IV.in","r");
    int s;
    while(~fscanf(fp,"%d",s)){
    a.xx.xx=s;
    fscanf(fp,"%d",s);
    a.xx.yy=s;
    fscanf(fp,"%d",s);
    a.yy.xx=s;
    fscanf(fp,"%d",s);
    a.yy.yy=s;
    IVList.push_back(a);
    }
    fclose(fp);
    printf("\n The end of input of dictionary \n");

}
int main(void){
    //�����ļ�
    //��ʽ��
    //ÿ�����ݰ�һ�У�����IV�����������Լ����ĵĵ�һ������һ���ĸ������ÿո����
    //�ļ�����IV.in
    IV_read();
    RecoverWEPkey();
return 0;
}
