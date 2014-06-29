#include<iostream>
#include<algorithm>
#include<vector>
#include<fstream>
#include<string>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<map>
#include<list>
#include<cmath>
#include<sstream>
using namespace std;
struct MI
{
    string subject;
    map<double,vector<string> > MIscores;
};
struct Course
{
    string title;
    string subjects;
    string univ;
    string text;
    vector<string> vec;
};
vector<string> stopWords;
map<string,string> stemMap;
map< string, vector<string> >classTextMap;
vector<string> biovec;vector<string> mathvec;vector<string>chemvec;
vector<string> AIvec;vector<string>theoryvec;vector<string>statsvec;vector<string>ecovec;
void buildClassTextMap()
{
    classTextMap["BIOLOGY&LIFE_SCIENCES"]=biovec;
    classTextMap["MATHEMATICS"]=mathvec;
    classTextMap["CHEMISTRY"]=chemvec;
    classTextMap["CompSci_AI"]=AIvec;
    classTextMap["CompSci_Theory"]=theoryvec;
    classTextMap["STATISTICS_DA"]=statsvec;
    classTextMap["ECONOMICS"]=ecovec;
}
void buildStemMap()
{
    stemMap["model"]="modeling";stemMap["models"]="modeling";stemMap["signal"]="signaling";stemMap["computational"]="computing";
    stemMap["epigenetic"]="epigenetics";stemMap["genome"]="genomics";stemMap["genomic"]="genomics";stemMap["disorders"]="disease";
    stemMap["gene"]="genetics";stemMap["cell"]="cellular";stemMap["analyse"]="analysis";stemMap["predictor"]="predictors";
    stemMap["economic"]="economics";stemMap["random"]="randomness";stemMap["computation"]="computing";stemMap["computations"]="computing";
    stemMap["society"]="social";stemMap["experiment"]="experiments";stemMap["biological"]="biology";stemMap["behaviour"]="behavioural";
}
vector<string> stem(vector<string> swtext)
{
    vector<string> stemRet;
    vector<string> :: iterator vit;
    for(vit=swtext.begin();vit!=swtext.end();vit++)
    {
        map<string, string>::iterator mit = stemMap.find(*vit);
        if (mit == stemMap.end()) { stemRet.push_back(*vit); /* Not found */ }
        else {  stemRet.push_back(mit->second); /* i->first will contain "apple", i->second will contain 5 */ }
    }
    return stemRet;
}
void buildSWList()
{
    stopWords.push_back("in");stopWords.push_back("with");stopWords.push_back("the");stopWords.push_back("of");stopWords.push_back("which");stopWords.push_back("is");stopWords.push_back("important");
    stopWords.push_back("on");stopWords.push_back("and");stopWords.push_back("level");stopWords.push_back("for");stopWords.push_back("to");stopWords.push_back("identifying");stopWords.push_back("by");
    stopWords.push_back("between");stopWords.push_back("from");stopWords.push_back("a");stopWords.push_back("imprinting");stopWords.push_back("x");stopWords.push_back("stumbling");stopWords.push_back("comparison");
    stopWords.push_back("formal");stopWords.push_back("risky");stopWords.push_back("two");stopWords.push_back("versus");stopWords.push_back("taking");stopWords.push_back("types");stopWords.push_back("others");
    stopWords.push_back("shedding");stopWords.push_back("compared");stopWords.push_back("or");stopWords.push_back("three");stopWords.push_back("its");stopWords.push_back("vs");stopWords.push_back("examples");
    stopWords.push_back("as");stopWords.push_back("etc");stopWords.push_back("especially");stopWords.push_back("course");stopWords.push_back("basic");stopWords.push_back("claims");stopWords.push_back("theory");
}
bool stringCompare( const string &left, const string &right ){
   for( string::const_iterator lit = left.begin(), rit = right.begin(); lit != left.end() && rit != right.end(); ++lit, ++rit )
      if( tolower( *lit ) < tolower( *rit ) )
         return true;
      else if( tolower( *lit ) > tolower( *rit ) )
         return false;
   if( left.size() < right.size() )
      return true;
   return false;
}
void sortSWList()
{
    sort( stopWords.begin(), stopWords.end(), stringCompare );
}
bool isSW(string key)
{
    return binary_search( stopWords.begin(), stopWords.end(), key );
}
bool containsLetters(string sub)
{
    if(sub.size()==0 || sub.size()==1)return false;
    else return true;

}
vector<string> removeSW(string text)
{
    vector<string> retText;
    istringstream iss (text);
    do
    {
        string sub;
        iss >> sub;
        transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
        if(!isSW(sub))
        {
            if(containsLetters(sub))
            retText.push_back(sub);
        }
    }while(iss);
    return retText;

}
int main()
{
    ifstream trainData;
    ofstream trainScan;
    trainScan.open("/home/sumit/Desktop/Assignment-2/TrainScan.txt");
    trainData.open("/home/sumit/Desktop/Assignment-2/TrainingData.txt");
    list<string> *univCourses;
    int numCourses=37;
    string temp;
    vector<Course> courseList;
    for(int i=0;i<numCourses;i++)
    {
        struct Course obj;
        getline(trainData,temp);
        obj.title=temp;
        getline(trainData,temp);
        obj.subjects=temp;
        getline(trainData,temp);
        obj.univ=temp;
        while ((getline(trainData,temp)))
        {
            if(temp=="END"){break;}
            obj.text += temp;
            obj.text += " ";
        }
        courseList.push_back(obj);
    }
    map<string,int> univRank;
    univRank["Icahn School of Medicine at Mount Sinai"]=0;
    univRank["The University of Chicago"]=1;
    univRank["The University of Melbourne"]=2;
    univRank["University of Minnesota"]=3;
    univRank["Higher School of Economics"]=4;
    univRank["Rice University"]=5;
    univRank["Moscow Institute of Physics and Technology"]=6;
    univRank["École normale supérieure"]=7;
    univRank["Stanford University"]=8;
    univRank["Northwestern University"]=9;
    univRank["École Polytechnique Fédérale de Lausanne"]=10;
    univRank["University of Toronto"]=11;
    univRank["Columbia University"]=12;
    univRank["University of Michigan"]=13;
    univRank["Ludwig-Maximilians-Universität München (LMU)"]=14;
    univRank["University of Washington"]=15;
    univRank["Johns Hopkins University"]=16;
    univRank["Georgia Institute of Technology"]=17;
    univRank["Fudan University"]=18;
    univRank["Duke University"]=19;
    univRank["University of California, Irvine"]=20;
    univCourses=new list<string>[21];
    for(int i=0;i<courseList.size();i++)
    {
        string univ=courseList[i].univ;
        int toInsert=univRank[univ];
        univCourses[toInsert].push_back(courseList[i].title);
    }
    buildSWList();
    sortSWList();
    buildStemMap();
    //for(int i=0;i<courseList.size();i++)
    //{
    //    trainScan<<courseList[i].title<<endl;
    //    trainScan<<courseList[i].univ<<endl;
    //    trainScan<<courseList[i].subjects<<endl<<endl;
    //}
    //for(int i=0;i<courseList.size();i++)
    //{
    //    trainScan<<courseList[i].text<<endl<<endl;
    //}
    //vector<string>::iterator vit;
    //for(vit=stopWords.begin();vit!=stopWords.end();vit++)
    //{
    //    trainScan<<*vit<<endl;
    //}
    buildClassTextMap();
    for(int i=0;i<courseList.size();i++)
    {
        string text=courseList[i].text;
        vector<string> swtext=removeSW(text);
        vector<string> :: iterator viter;
        for(viter=swtext.begin();viter!=swtext.end();viter++)
        {
            courseList[i].vec.push_back(*viter);
        }
        //vector<string> :: iterator vit;
        //for(vit=swtext.begin();vit!=swtext.end();vit++)
        //{
        //    trainScan<<*vit<<",";
        //}
        //trainScan<<endl;
        vector<string> stemtext=stem(swtext);
        vector<string> :: iterator vit;
        //for(vit=stemtext.begin();vit!=stemtext.end();vit++)
        //{
        //    trainScan<<*vit<<",";
        //}
        //trainScan<<endl;
        istringstream iss (courseList[i].subjects);
        vector<string> classes;
        string classSub;
        while(iss)
        {
            iss>>classSub;
            classes.push_back(classSub);
        }
        vector<string>::iterator it;
        //for(it=classes.begin();it!=(classes.end()-1);it++)
        //{
        //    trainScan<<*it<<" ";
        //}
        //trainScan<<endl;
        vector<string> :: iterator cvit;
        vector<string> :: iterator tvit;
        for(cvit=classes.begin();cvit!=(classes.end()-1);cvit++)
        {
            //cout<<*cvit<<" ";
            map<string, vector<string> >::iterator mit = classTextMap.find(*cvit);
            for(tvit=stemtext.begin();tvit!=stemtext.end();tvit++)
            {
                mit->second.push_back(*tvit);
            }
        }
        //cout<<endl;
    }
    //for(map<string,vector<string> >::iterator iter = classTextMap.begin(); iter != classTextMap.end(); ++iter)
    //{
    //    trainScan << iter->first<<endl;
    //    vector<string> :: iterator vit;
    //    for(vit=iter->second.begin();vit!=iter->second.end();vit++)
    //    {
    //        trainScan<<*vit<<" ";
    //    }
    //    trainScan<<endl<<endl;
    //}
    //for(int i=0;i<courseList.size();i++)
    //    trainScan<<courseList[i].vec.size()<<endl;
    map<int,string>classRank;
    classRank[0]="BIOLOGY&LIFE_SCIENCES";
    classRank[1]="MATHEMATICS";
    classRank[2]="CHEMISTRY";
    classRank[3]="CompSci_AI";
    classRank[4]="CompSci_Theory";
    classRank[5]="STATISTICS_DA";
    classRank[6]="ECONOMICS";
    MI* classesMI = new MI[7];
    for(int j=0;j<7;j++)
    {
        string word;
        classesMI[j].subject=classRank[j];
        //cout<<classesMI[i].subject<<endl;
        map<string, vector<string> >::iterator mit = classTextMap.find(classRank[j]);
        vector<string> :: iterator it;
        for(it=mit->second.begin();it!=mit->second.end();it++)
        {
            word=*it;
            int N=0,N0=0,N1=0,N10=0,N11=0,N00=0,N01=0;
            for(int i=0;i<courseList.size();i++)
            {
                N++;
                vector<string> :: iterator vit;
                bool termFound=false;
                for(vit=courseList[i].vec.begin();vit!=courseList[i].vec.end();vit++)
                {
                    if((*vit).compare(word)==0)
                    {
                        if(!termFound){
                            N1++;
                            termFound=true;
                            istringstream sss (courseList[i].subjects);
                            string sub;
                            bool classfound=false;
                            while(sss)
                            {
                                sss>>sub;
                                if(sub.compare(classRank[j]))
                                {
                                    if(!classfound && termFound)
                                    {
                                        N11++;
                                        classfound=true;
                                    }
                                }
                            }
                            if(!classfound){N10++;}
                        }
                    }
                }
                if(!termFound)
                {
                    N0++;
                    istringstream sss (courseList[i].subjects);
                    string sub;
                    bool classfound=false;
                    while(sss)
                    {
                        sss>>sub;
                        if(sub.compare(classRank[j]))
                        {
                            if(!classfound){
                                N01++;
                                classfound=true;
                            }
                        }
                    }
                    if(!classfound){N00++;}
                }
            }
            //trainScan<<word<<" "<<N<<" "<<N0<<" "<<N1<<" "<<N00<<" "<<N01<<" "<<N10<<" "<<N11<<endl;
            double MI;
            MI=(double)(N11/(double)N)*(double)log2((double)1+(N*(double)N11)/(double)(N1*(double)N1))+(double)(N01/(double)N)*(double)log2((double)1+(N*(double)N01)/(double)(N0*(double)N1))+(double)(N10/(double)N)*(double)log2(1+(N*(double)N10)/(double)(N1*(double)N0))+(double)(N00/(double)N)*(double)log2(1+(N*(double)N00)/(double)(N0*(double)N0));
            //trainScan<<word<<" "<<MI<<endl;
            classesMI[j].MIscores[MI].push_back(word);
        }
    }
    //for(int j=0;j<7;j++)
    //{
    //    for(map<double,vector<string> >:: iterator mit=classesMI[j].MIscores.begin();mit!=classesMI[j].MIscores.end();mit++)
    //    {
    //        trainScan<<mit->first<<" ";
    //        vector<string> :: iterator vit;
    //        for(vit=mit->second.begin();vit!=mit->second.end();vit++)
    //        {
    //            trainScan<<*vit<<" ";
    //        }
    //        trainScan<<endl;
    //    }
    //    trainScan<<endl;
    //}

    return 0;
}
