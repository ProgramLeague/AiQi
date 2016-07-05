#ifndef LINK_struct 
#define LINK_struct

struct LINK_UNIT{ 
	              int linker_ID;      //连接者的ID
                  float linker_weight;  //连接的强度

                  LINK_UNIT *next;


				  LINK_UNIT *ID_return_P(int ID);

                  void Init();
				  void New(int linker_ID);
                  float Get_weight(int linker_ID);
                  void Set_weight(int linker_ID,float linker_weight);
                  void Set_weight_ADD(int linker_ID,float ADD);
				  void Weight_Change(int linker_ID,float Change);
				  void Del_Linker(int linker_ID);
                  void FreeAll();



				  bool Find_linker_ID(int linker_ID);

				};









#endif
