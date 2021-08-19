#include <iostream>
#include <string>
#include <cstdlib>
#include "obj.h"
uint16_t vetex[200][200][200][9];
bool check_argument5(char**);
int check_argument9(char**);
bool check_argument13(char**);
bool Gen(int len, int wid, int hei, float s_len, float s_wid, float s_hei, float mv_len, float mv_wid, float mv_hei, std::string);
/* the coordinate
 *            |(y+) height
 * (z+)width / \ (x+) length
 *
 * */

int main(int argc, char* argv[]) {

    if(argc == 5)
    {
        if(check_argument5(argv))
        {
            Gen(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),
                1,1,1,
                0,0,0,argv[1]);
            return 0;
        }
    }
    else if(argc == 9)
    {
        switch(check_argument9(argv))
        {
            case 1:
                if(Gen(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),
                    atof(argv[6]),atof(argv[7]),atof(argv[8]),
                    0,0,0,argv[1]))
                    return 0;
                break;
            case 2:
               if(Gen(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),
                    1,1,1,
                    atof(argv[6]),atof(argv[7]),atof(argv[8]),argv[1]))
                   return 0;
               break;
            default:
                ;
        }

    }
    else if(argc == 13)
    {
        if(check_argument13(argv))
        {
            int len = atoi(argv[2]);
            int wid = atoi(argv[3]);
            int hei = atoi(argv[4]);
            float slen = atof(argv[6]);
            float swid = atof(argv[7]);
            float shei = atof(argv[8]);
            float mvlen = atof(argv[10]);
            float mvwid = atof(argv[11]);
            float mvhei = atof(argv[12]);
            if(Gen(len,wid,hei,
                   slen,swid,shei,
                   mvlen,mvwid,mvhei,argv[1]))
                return 0;
        }
    }
    std::cout << "using arguments in order (including -s(first) -m if both) in one line:" <<std::endl
    << "path <int> length <int> width <int> height "
    <<std::endl<<   "\t [-s]<float/int> (scale)length wid height "
    <<std::endl <<  "\t [-m]<float/int> (move)length wid height "
    << std::endl;
    return 0;

}
inline bool isScaleOK(float s){
    if (s <= 0)
    {
        std::cout << "Error: the scale of each dim should be greater than zero ." << std::endl;
        return false;
    }
    return true;
}
inline bool isLenOK(int Len){
    if(Len >=200 || Len <= 0)
    {
        std::cout << "Error: the nodes number of each dim should be in (0,200) integer." << std::endl;
        return false;
    }
    return true;
}
bool check_argument5(char**argv){
    int len = atoi(argv[2]);
    int wid = atoi(argv[3]);
    int hei = atoi(argv[4]);
    if(!isLenOK(len))return false;
    if(!isLenOK(wid))return false;
    if(!isLenOK(hei))return false;
    return true;
}
int check_argument9(char**argv){
    if(!check_argument5(argv))return 0;
    std::string arg = argv[5];
    std::string s = "s";
    std::string m = "m";
    if(arg.find(s) != std::string::npos){
        float slen = atof(argv[6]);
        float swid = atof(argv[7]);
        float shei = atof(argv[8]);
        if(!isScaleOK(slen))return 0;
        if(!isScaleOK(swid))return 0;
        if(!isScaleOK(shei))return 0;
        return 1;
    }
    if(arg.find(m) != std::string::npos)
        return 2;
    else
        return 0;
}

bool check_argument13(char**argv){
    if(!check_argument5(argv))return false;
    std::string args = argv[5];
    std::string argm = argv[9];
    std::string s = "s";
    std::string m = "m";
    if(args.find(s) != std::string::npos){
        float slen = atof(argv[6]);
        float swid = atof(argv[7]);
        float shei = atof(argv[8]);
        if(!isScaleOK(slen))return false;
        if(!isScaleOK(swid))return false;
        if(!isScaleOK(shei))return false;
    }else
        return false;
    if(argm.find(m) != std::string::npos)
        return true;
    else
        return false;

}
bool Gen(int len, int wid, int hei, float s_len, float s_wid, float s_hei, float mv_len, float mv_wid, float mv_hei, std::string arg){
    cube result(len,wid,hei,s_len,s_wid,s_hei,mv_len,mv_wid,mv_hei);
    result.fileroot(arg);
    if(result.print_vetex() && result.print_ele() && result.print_face() && result.print_boundary())
    {
        std::cout << "Print 9 files to " << result.filename << std::endl;
        return true;
    }
    return false;
}