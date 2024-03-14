// 10724128 �d�t�� 10727104 ���l��
// �i�u��j�V�i�sĶ�ﶵ�j�V�i�sĶ���j�Ŀ�i�sĶ�ɥ[�J�H�U�R�O�j
// �[�J�i-std=c++11�j �A�Y�i�B�@�C

# include<fstream>
# include<string.h>
# include<iostream>
# include<vector>
# include<cstdlib>
# include<iomanip>
# include<stack>
#include<math.h>
#include <time.h>
#define COLUMNS 6
#define MAX_LEN 10
#define BIG_INT 255
using namespace std;


struct Data {
    char  sid[10] ;
    char  name[10] ;
    unsigned char score1 ;
    unsigned char score2 ;
    unsigned char score3 ;
    unsigned char score4 ;
    unsigned char score5 ;
    unsigned char score6 ;
    float average=-1 ;
};// Ū����ƥΪ����c

struct hashData {
    char  sid[10] ;
    char  name[10] ;
    unsigned char score1 ;
    unsigned char score2 ;
    unsigned char score3 ;
    unsigned char score4 ;
    unsigned char score5 ;
    unsigned char score6 ;
    float average = -1;
    bool empty = true ;
};// Ū����ƥΪ����c

class HashTable {
	private:
    	vector< Data> list ;
    	string inputString ;
    public:
        string getFileName(  ) { //
            return inputString ;
        }
		string readTheFile(  ) { // Ū��
			int tab = 0 ,input = 1, num = 1 ;
			char ch ;
  			cout << endl << "Input a file number (e.g., 301, 302, ...): " ;
  			cin >> inputString ; // �Nint�ɦW�নstring
  			fstream theFile;
  			int  dataNum ;
  			Data temp ;
  			string fileName = "input" + inputString + ".bin" ;
             theFile.open( fileName.c_str(), ios::in | ios::binary ) ;
  			if ( theFile.is_open() ) { // �p�G�����}�ɮ�
				theFile.seekg( 0, theFile.end ) ;
                dataNum = theFile.tellg() / sizeof( temp );
                theFile.seekg( 0, theFile.beg ) ;

                for ( int i = 0 ; i < dataNum ; i ++ ) {
                    theFile.read( (char*)&temp, sizeof(temp) ) ;
                    list.push_back( temp ) ;
                } // end for

    			theFile.close();
    			return "0" ;
    		} //  read .bin
    		else {
                    cout << "�S�����w��bin��" <<endl ;
                    return inputString ;
    		} //  read
		} // readTheFile

		void readBin ( ) {
		    fstream theFile;
		    string fileName = "input" + inputString + ".bin" ;
  			int  dataNum ;
  			Data temp ;
            theFile.open( fileName.c_str(), ios::in | ios::binary ) ;
  			if ( theFile.is_open() ) { // �ˬd�ɮ׬O�_���}
				theFile.seekg( 0, theFile.end ) ;
                dataNum = theFile.tellg() / sizeof( temp ); // Ū���ɮפj�p
                theFile.seekg( 0, theFile.beg ) ;

                for ( int i = 0 ; i < dataNum ; i ++ ) {
                    theFile.read( (char*)&temp, sizeof(temp) ) ;
                    list.push_back( temp ) ;
                } // end for

    			theFile.close();
            }
		}

        void insertLinear () {
            int dataNum = list.size() ;
            int hashSize = findHashSize(dataNum*1.2 ) ;
             vector<Data> theHash(hashSize) ;
             vector<int> tableNum(hashSize) ;
             fstream outputFile ;
            int count = 0 ;
            string fileName = "linear" + inputString + ".txt" ;
            outputFile.open( fileName, ios::out ) ;
            for ( int i = 0 ; i < dataNum ; i ++ ) {
                int sidSize = strlen(list.at(i).sid);
                int key = 1 ;
                for( int j = 0 ; j < sidSize ; j ++ ) { // ��X key
                    key *= (int)list.at(i).sid[j] ;
                    key = key % hashSize ;
                } // end for
                int keep = key ;
                if ( theHash.at(key).average == -1 ) { // ���Ʃ�J��mkey
                    for ( int k = 0 ;  k< 10 ; k++) {
                        theHash.at(key).sid[k] = list.at(i).sid[k] ;
                        theHash.at(key).name[k] = list.at(i).name[k] ;
                    }
                    theHash.at(key).score1 = list.at(i).score1 ;
                    theHash.at(key).score2 = list.at(i).score2 ;
                    theHash.at(key).score3 = list.at(i).score3 ;
                    theHash.at(key).score4 = list.at(i).score4 ;
                    theHash.at(key).score5 = list.at(i).score5 ;
                    theHash.at(key).score6 = list.at(i).score6 ;
                    theHash.at(key).average = list.at(i).average ;
                     tableNum.at(key) = key ;
                    count ++ ;
                }
                else { // �I��
                    int originKey = key ;
                    while ( theHash.at(key).average != -1 ) {
                        //    cout << "1" << endl ;
                        key++ ;
                        if ( key >= hashSize ) key = 0 ;
                        count ++ ;
                    } // �v�@���U�M��

                    for ( int k = 0 ;  k< 10 ; k++) {
                        theHash.at(key).sid[k] = list.at(i).sid[k] ;
                        theHash.at(key).name[k] = list.at(i).name[k] ;
                    }
                    theHash.at(key).score1 = list.at(i).score1 ;
                    theHash.at(key).score2 = list.at(i).score2 ;
                    theHash.at(key).score3 = list.at(i).score3 ;
                    theHash.at(key).score4 = list.at(i).score4 ;
                    theHash.at(key).score5 = list.at(i).score5 ;
                    theHash.at(key).score6 = list.at(i).score6 ;
                    theHash.at(key).average = list.at(i).average ;
                    tableNum.at(key) = originKey ;
                    count ++ ;
               //     cout << "3" << endl ;
                } // end else

            } // end for
            outputFile << " --- Hash Table --- (linear probing)" << endl ;
            for ( int i = 0 ; i < theHash.size() ; i ++ ) {
                if ( theHash.at(i).average == -1 )
                    outputFile << "[" << i << "]" << "" << endl ;
                else
                    outputFile << "[" << i << "]\t" << tableNum.at(i) << ",\t" << theHash.at(i).sid << ",\t" << theHash.at(i).name << ",\t" << (float)theHash.at(i).average << endl ;
            }
            outputFile.close() ;
            searchLinear( theHash) ;
            cout << "Successful Search : " << (float) count / dataNum << endl ;
            list.clear() ;
        }

        void searchLinear( vector<Data> theHash) {
            float count = 0 ;
            for ( int i = 0 ; i < theHash.size() ; i ++ ) {
                int j = i ;
                if ( theHash.at(i).average != -1 ) {
                    while( theHash.at(j).average != -1 ) {
                        count++ ;
                        j ++ ;
                        if ( j >= theHash.size() )
                            j = 0 ;
                    }
                }
            }
            cout << "Unsuccessful Search : " << count / theHash.size() << endl ;
        }

        int findHashSize ( int dataNum) {
            dataNum++ ;
            if ( dataNum == 2 ) return 2 ;
            else if ( dataNum == 3 ) return 3 ;
            for ( int i=3; i <= dataNum/2; i++) {
                if (dataNum % i == 0)
                    return findHashSize( dataNum ) ;
            } // end for

            return dataNum ;
        }

        void searchQuadratic( vector<Data> theHash) {
            float count = 0 ;
            for ( int i = 0 ; i < theHash.size() ; i ++ ) {
                int j = i, k = 1 ;
                if ( theHash.at(i).average != -1 ) {
                    while ( theHash.at(j).average != -1 ) {
                        j = i ;
                        j += pow( k, 2 ) ;
                        j = j % theHash.size() ;
                        k ++ ;
                        count ++ ;
                    }
                }
            }
        cout << "Unsuccessful search : " << count / theHash.size() << endl ;

        }

         void insertQuadratic () {
            int dataNum = list.size() ;
            int hashSize = findHashSize(dataNum*1.2 ) ;
             vector<Data> theHash(hashSize) ;
             vector<int> tableNum(hashSize) ;
             fstream outputFile ;
            int count = 0 ;
            string fileName = "quadratic" + inputString + ".txt" ;
            outputFile.open( fileName, ios::out ) ;
            for ( int i = 0 ; i < dataNum ; i ++ ) {
                int sidSize = strlen(list.at(i).sid);
                int key = 1 ;
                for( int j = 0 ; j < sidSize ; j ++ ) { // ��X key
                    key *= (int)list.at(i).sid[j] ;
                    key = key % hashSize ;
                } // end for
                int keep = key ;
                if ( theHash.at(key).average == -1 ) { // ���Ʃ�J��mkey
                    for ( int k = 0 ;  k< 10 ; k++) {
                        theHash.at(key).sid[k] = list.at(i).sid[k] ;
                        theHash.at(key).name[k] = list.at(i).name[k] ;
                    }
                    theHash.at(key).score1 = list.at(i).score1 ;
                    theHash.at(key).score2 = list.at(i).score2 ;
                    theHash.at(key).score3 = list.at(i).score3 ;
                    theHash.at(key).score4 = list.at(i).score4 ;
                    theHash.at(key).score5 = list.at(i).score5 ;
                    theHash.at(key).score6 = list.at(i).score6 ;
                    theHash.at(key).average = list.at(i).average ;
                     tableNum.at(key) = key ;
                    count ++ ;
                }
                else { // �I��
                    int walkCount = 1, originKey = key ;
                    while ( theHash.at(key).average != -1 ) {
                        key = originKey ;
                        key += pow( walkCount, 2 ) ; // K���G��
                        key = key % theHash.size() ;
                        walkCount ++ ;
                        if ( walkCount >= 9999 ) {
                            cout << "This file can not run in Quadratic  Probing\n" ;
                            return ;
                        }
                        count ++ ;
                    } // end while

                    for ( int k = 0 ;  k< 10 ; k++) {
                        theHash.at(key).sid[k] = list.at(i).sid[k] ;
                        theHash.at(key).name[k] = list.at(i).name[k] ;
                    }
                    theHash.at(key).score1 = list.at(i).score1 ;
                    theHash.at(key).score2 = list.at(i).score2 ;
                    theHash.at(key).score3 = list.at(i).score3 ;
                    theHash.at(key).score4 = list.at(i).score4 ;
                    theHash.at(key).score5 = list.at(i).score5 ;
                    theHash.at(key).score6 = list.at(i).score6 ;
                    theHash.at(key).average = list.at(i).average ;
                    tableNum.at(key) = originKey ;
                    count ++ ;
                } // end �I��

            } // end for
            outputFile << " --- Hash Table --- (quadratic probing)" << endl ;
            for ( int i = 0 ; i < theHash.size() ; i ++ ) {
                if ( theHash.at(i).average == -1 )
                    outputFile << "[" << i << "]" << "" << endl ;
                else
                    outputFile << "[" << i << "]\t" << tableNum.at(i) << ",\t" << theHash.at(i).sid << ",\t" << theHash.at(i).name << ",\t" << (float)theHash.at(i).average << endl ;
            }
            outputFile.close() ;
            searchQuadratic( theHash) ;
            cout << "Successful Search : " << (float) count / dataNum << endl ;
            list.clear() ;
        }
};
// --------------------------Double Hash-------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct sT {
	char sid[MAX_LEN];
	char sname[MAX_LEN];
	unsigned char score[COLUMNS];
	float mean;
}studentType;



class Double {
private:
	string fileName; // �ɮצW��
	int total; // ����`����
	int size; // �����j�p
	int heighStep; // �̰��B��
	studentType *table; // ������Ʀb�������m
	int *hvalue; // ������ƪ������
	float successful ; // �����j�M�{�s��
public:
	Double() { // �غc�l
		total = 0;
		size = 0;
		heighStep = 0;
		successful = 0;
		table = NULL;
		hvalue = NULL;
	}

	void SetSize() { // �]�w�����j�p
		size = total * 1.2;
		size++;
		bool keep = true;

		// *************** ��̤p��� ***************** //
		while ( keep ) {
			int fact = 0;
			for ( int i = 1 ; i <= sqrt(size) ; i++ ) {
				if ( size % i == 0 ) {
					fact++;
				}

				if ( fact >= 2 ) {
					break;
				}
			}

			if ( fact == 1 ) {
				keep = false;
			}

			else if ( keep ) {
				size++;
			}
		}

		// *************** ��̤p��� ***************** //
	}

	void SetFileName( string name ) { // �]�w�ɮצW��
		fileName = name;
	}

	void SetHeightStep() { // �]�w�̰��B��
		heighStep = total / 3;
		heighStep++;

		// *************** ��̤p��� ***************** //
		bool keep = true;
		while ( keep ) {
			int fact = 0;
			for ( int i = 1 ; i <= sqrt( heighStep ) ; i++ ) {
				if ( heighStep % i == 0 ) {
					fact++;
				}

				if ( fact >= 2 ) {
					break;
				}
			}

			if ( fact == 1 ) {
				keep = false;
			}

			else if ( keep ) {
				heighStep++;
			}
		}

		// *************** ��̤p��� ***************** //

	}

	/*
	bool CheckBinary() { // �O�_�s�b".bin"
		fstream binFile;
		string testName = "input" + fileName + ".bin";
		binFile.open( testName.c_str(), fstream::in | fstream::binary );
		if ( binFile.is_open() ) {
			return true;
		}
		else {
			return false;
		}
	}
	*/

	bool TransForm() { // �N ".txt" �ഫ�� ".bin"
		fstream inFile;
		fstream outFile;
		studentType oneSt;
		int stNo = 0;
		do {
			if ( !fileName.compare( "0" ) )
				return false;
			inFile.open( ( "input" + fileName + ".txt").c_str(), fstream::in );
			if ( inFile.is_open() )
				break;
			else {
				return false;
			}

		} while(true);

		string testName = "input" + fileName + ".bin";
		outFile.open( testName.c_str(), fstream::out | fstream::binary );
		if ( outFile.is_open() ) {
			char rBuf[BIG_INT];

			while ( inFile.getline( rBuf, BIG_INT, '\n') ) {
				string temp;
				int cNo = 0, pre = 0, pos = 0;

				stNo++;
				temp.assign( rBuf );
				pos = temp.find_first_of( '\t', pre );

				while ( pos != string::npos ) {
					switch ( ++cNo ) {
						case 1 : strcpy( oneSt.sid, temp.substr( pre, pos-pre ).c_str() );
							break;
						case 2 : strcpy( oneSt.sname, temp.substr( pre, pos-pre ).c_str() );
							break;
						default : oneSt.score[cNo-3] = atoi( temp.substr( pre, pos-pre ).c_str() );
							break;
					}

					pre = ++pos;
					pos = temp.find_first_of('\t', pre );
				}

				pos = temp.find_last_of('\t');
				oneSt.mean = atof( temp.substr(pos+1).c_str() );
				outFile.write( (char*)&oneSt, sizeof(oneSt));
			}

			outFile.close();
		}

		inFile.close();
		total = stNo;
		SetSize();
		return true;
	}

	int Hash( studentType oneSt ) {	// ������
		unsigned long long num = 1;
		for ( int i = 0 ; i < strlen(oneSt.sid) ; i++ ) {
			num = num * oneSt.sid[i] ;
		}

		return num % size;
	}

	int Step( studentType oneSt ) { // �B�����
		unsigned long long num = 1;

		// �Ǹ��C�Ӧr���̾�ASCII�ۭ�
		for ( int i = 0 ; i < strlen(oneSt.sid) ; i++ ) {
			num = num * oneSt.sid[i] ;
		}

		return ( heighStep - ( num % heighStep ) );
	}

	void BulidTable( studentType oneSt ) { // �إ������

		// ****************** ������l�� ************************* //
		if ( table == NULL ) {
			table = new studentType[size];
			hvalue = new int[size];
			for ( int i = 0 ; i < size ; i++ ) {
				for ( int j = 0 ; j < strlen( table[i].sid ) ; j++ ) {
					table[i].sid[j] = '\0';
				}

				for ( int k = 0 ; k < strlen( table[i].sname ) ; k++ ) {
					table[i].sname[k] = '\0';
				}

				hvalue[i] = -1;
			}
		}
		// ****************** ������l�� ************************* //

		int key = Hash( oneSt ); // ���o����ƭ�
		successful++;
		if ( table[key].sid[0] == '\0' ) { // �̾�����ȩ�J�����
			strcpy( table[key].sid, oneSt.sid );
			strcpy( table[key].sname, oneSt.sname );
			table[key].mean = oneSt.mean;
			hvalue[key] = key;
		}

		else { // ������w�g�����

			// �H��e�������Ȭ���ǡA���_�W�[�B���A����U�@������Ȥ���Ƭ��� //
			int step = Step( oneSt );
			int nextkey = key + step;
			successful++;
			if ( nextkey >= size ) { // ����ȶW�X�����j�p
				nextkey = nextkey - size;
			}

			while ( table[nextkey].sid[0] != '\0' ) {
				nextkey = nextkey + step;
				successful++;
				if ( nextkey >= size ) { // ����ȶW�X�����j�p
					nextkey = nextkey - size;
				}
			}

			strcpy( table[nextkey].sid, oneSt.sid );
			strcpy( table[nextkey].sname, oneSt.sname );
			table[nextkey].mean = oneSt.mean;
			hvalue[nextkey] = key;

			// �H��e�������Ȭ���ǡA���_�W�[�B���A����U�@������Ȥ���Ƭ��� //
		}
	}

	void ReadBin() { // Ū ".bin"
		int stNo = 0;
		fstream binFile;
		studentType oneSt;
		string testName = "input" + fileName + ".bin";
		binFile.open( testName.c_str(), fstream::in | fstream::binary );

		if ( binFile.is_open() ) {

			binFile.seekg( 0, binFile.end );
			stNo = binFile.tellg() / sizeof( oneSt ) ;//Ū���ɮפj�p
			binFile.seekg( 0, binFile.beg ) ;
			if ( total == 0 ) {

				total = stNo;
				SetSize();
				SetHeightStep();

			}

			binFile.seekg( 0, binFile.beg );
			for ( int i = 0 ; i < stNo ; i++ ) {
				binFile.read( (char*)&oneSt, sizeof( oneSt ) );
				BulidTable( oneSt );
			}

			binFile.close();
		}
	}

	void Write() { // ��X�ɮ�
		fstream outFile;
		string testName = "double" + fileName + ".txt";
		outFile.open( ( testName ).c_str(), ios::out );
		if ( outFile.fail() ) {
			cout << "�ɮ׵L�k�}��!!!\n\n\n";
		}

		else {
			outFile << " --- Hash table created by Double hashing    ---\n";
			for ( int i = 0 ; i < size ; i++ ) {
				outFile << "[ " << i << "]\t";
				if ( hvalue[i] != -1 && table[i].sid[0] != '\0' ) {
					outFile << hvalue[i] << ",\t";
					outFile << table[i].sid << ",\t";
					outFile << table[i].sname << ",\t";
					outFile << table[i].mean << "\n";
				}

				else {
					outFile << endl;
				}
			}

			outFile << " -----------------------------------------------------\n";
			outFile.close();
		}
	}

	void Reset() { // ��l��
		total = 0;
		size = 0;
		heighStep = 0;
		successful = 0;
		hvalue = NULL;
		table = NULL;
	}

	void Output() { // ��X��ù��W
		cout << "�ϥ��������겣�������!!!\n\n"
			 << "successful search: "
		     << fixed << setprecision(4) << successful / total
		     << " comparisons on average\n\n";
	}
};
int main(void) {
	int command = -1;
	HashTable hashTable ;
	fstream file;
	Double dbHash;
	string fileName ;
	bool haveFile = true ;
	bool exe = false;
    double start = 0.0, end = 0.0 ;
	while ( command != 0 ) {
		cout << endl;
		cout << "*===========HASH=============*\n"
			 << "*  1.Linear Probing          *\n"
			 << "*  2.Double Hash             *\n"
			 << "*  3.Quadratic  Probing      *\n"
			 << "*  0. EXIT.                  *\n"
			 << "*============================*\n\n"
			 << "Please input your command :  " ;
		cin >> command;
		if ( command == 1 ) {
			exe = false;
			haveFile = true ;
            string returnTemp = hashTable.readTheFile() ;
            if ( returnTemp != "0" ) {
                dbHash.SetFileName( returnTemp );
                if (dbHash.TransForm() )
                    hashTable.readBin() ;
                else {
                    cout << "�S�����w��txt�ɡA�Э��s��J" <<endl ;
                    haveFile = false ;
                }
            }

            if (exe == false && haveFile) {
            	hashTable.insertLinear() ;
            	exe = true;
			}


			cout << endl ;
		}
		else if ( command == 2 ) {
            dbHash.Reset();
			fileName = hashTable.getFileName() ;
			if ( exe ) {
				dbHash.SetFileName( fileName );
				dbHash.ReadBin();
				dbHash.Write();
				dbHash.Output();
				dbHash.Reset();
			}

			else {
				cout << "�Х����� 1.Linear Probing.\n\n\n";
			}

		}
        else if ( command == 3 ) {
            hashTable.readBin() ;
            if (exe) {
            	hashTable.insertQuadratic() ;
			}
			else {
				cout << "�Х����� 1.Linear Probing.\n\n\n";
			}
			cout << endl ;
        }
		else if ( command != 0 ) {
			cout << endl << "Error !!! �п�J���T�����O!!!\n\n" ;
		}
	}

	cout << endl << "����!" << endl;
}
