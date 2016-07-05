#ifndef Contacts_Struct 
#define Contacts_Struct

struct CONTACTS_UNIT  //联系表数据结构
		{ 
		 int ID;        //ID

                 CString data;  //数据内容
                 float weight;  //权值

		 CONTACTS_UNIT *next;




		 void Init();
		 void New(CString data);
		 void Add(CString data,float weight);

		 CONTACTS_UNIT *ID_return_P(int ID);
		 CONTACTS_UNIT *data_return_P(CString data);
		 void Set_data(CString data);
		 void Set_data(int index,CString data);
		 CString Get_n_data(int n);
		 void Set_weight(int index,float weight);
		 void Set_weight_ADD(int index,float ADD);
		 float Get_n_weight(int n);

		 void Del(int ID);
		 void Del(CString data);
		 void Del_All_Child();
		 void FreeAll();
		 int Get_Sum();
		 int Find_Data_Return_N(CString data);


		};






#endif
