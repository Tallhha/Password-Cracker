#include <stdio.h>
#include <unistd.h>
#include <crypt.h>
#include <iostream>
#include <string>
#include <cstring>
#include <mpi.h>
#include<omp.h>
#include <fstream>
using namespace std;

/*
Convert String to Charecter Array.
This function takes a string as input and converts it into a char array and returns it. 
*/
char *str_to_char(string s)
{
    char *id = new char[s.size() + 1];
    s.copy(id, s.size() + 1);
    id[s.size()] = '\0';
    return id;
}

/*
This function searches for the password using brute force.
It starts with a single digit 'a' as password and checks for all combinations of words from 'a' to 'zzzzzzzz'.
The password should be only small letters alphabets and max length should be 8.
It returns the password if it's found else it returns NULL.
*/

//Global Signal Variable to inform processes to stop searching if password is found.
int signal = 0;

char *brute_force(char salt[], char result[], string start, int alphabets)
{
    string pw = start;
    char reset = start[0];
    bool two_len = false, three_len = false, four_len = false, five_len = false, six_len = false, seven_len = false, eight_len = false;
    int one = 0, two = 0, three = 0, four = 0, five = 0, six = 0, seven = 0, eight = 0;
    int loop_one = alphabets, loop_two = alphabets, loop_three = alphabets, loop_four = alphabets, loop_five = alphabets, loop_six = alphabets, loop_seven = alphabets, loop_eight = alphabets;
    char reset1 = reset, reset2 = reset, reset3 = reset, reset4 = reset, reset5 = reset, reset6 = reset, reset7 = reset, reset8 = reset; 
    start = "a";
    while (eight <= loop_eight)
    {
        if(signal)
            break;
        if (eight == 1 && !eight_len)
        {
            //If password is not seven letters, Increase alphabet.
            pw += start;
            eight_len = true;
        }
        else if (eight > 1)
        {
            //Check all combinations of eight length.
            int length = pw.length();
            pw[length - 8] += 1;
        }

        while (seven <= loop_seven)
        {
            if(signal)
                break;
            if (seven == 1 && !seven_len)
            {
                //If password is not six letters, Increase alphabet.
                pw += start;
                seven_len = true;
            }
            else if (seven > 1)
            {
                //Check all combinations of seven length.
                int length = pw.length();
                pw[length - 7] += 1;
            }

            while (six <= loop_six)
            {
                if(signal)
                    break;
                if (six == 1 && !six_len)
                {
                    //If password is not five letters, Increase alphabet.
                    pw += start;
                    six_len = true;
                }
                else if (six > 1)
                {
                    //Check all combinations of six length.
                    int length = pw.length();
                    pw[length - 6] += 1;
                }

                while (five <= loop_five)
                {
                    if(signal)
                        break;
            
                    if (five == 1 && !five_len)
                    {
                        //If password is not four letters, Increase alphabet.
                        pw += start;
                        five_len = true;
                    }
                    else if (five > 1)
                    {
                        //Check all combinations of five length.
                        int length = pw.length();
                        pw[length - 5] += 1;
                    }

                    while (four <= loop_four)
                    {
                        if(signal)
                            break;
            
                        if (four == 1 && !four_len)
                        {
                            //If password is not three letters, Increase alphabet.
                            pw += start;
                            four_len = true;
                        }
                        else if (four > 1)
                        {
                            //Check all combinations of four length.
                            int length = pw.length();
                            pw[length - 4] += 1;
                        }

                        while (three <= loop_three)
                        {
                            if(signal)
                                break;
            
                            if (three == 1 && !three_len)
                            {
                                //If password is not two letters, Increase alphabet.
                                pw += start;
                                three_len = true;
                            }
                            else if (three > 1)
                            {
                                //Check all combinations of three length.
                                int length = pw.length();
                                pw[length - 3] += 1;
                            }

                            while (two <= loop_two)
                            {
                                if(signal)
                                    break;

                                if (two == 1 && !two_len)
                                {
                                    //If password is not one letter, Increase alphabet.
                                    pw += start;
                                    two_len = true;
                                }
                                else if (two > 1)
                                {
                                    //Check all combinations of two length.
                                    int length = pw.length();
                                    pw[length - 2] += 1;
                                }

                                while (one < loop_one)
                                {
                                    char *id = str_to_char(pw);
                                    char *encrypted = crypt(id, salt);
                                    //cout<<id<<endl;

                                    //If password found.
                                    if (strcmp(result, encrypted) == 0)
                                    {
                                        cout<< "\nPassword is: "<<id<<endl;
                                        cout<<"\nPassword Successfully Cracked."<<endl;
                                        return id;
                                    }

                                    //Check all Combinations of one length.
                                    int length = pw.length();
                                    pw[length - 1] += 1;
                                    one++;
                                }
                                two++;
                                //Reset Variables
                                one = 0;
                                loop_one = 26;
                                int length = pw.length();
                                pw[length - 1] = reset1;
                                reset1 = 'a';
                                
                            }
                            three++;
                            //Reset Variables
                            two = 1;
                            loop_two = 26;
                            int length = pw.length();
                            pw[length - 2] = reset2;
                            reset2 = 'a';
                        }
                        four++;
                        //Reset Variables
                        three = 1;
                        loop_three = 26;
                        int length = pw.length();
                        pw[length - 3] = reset3;
                        reset3 = 'a';
                    }
                    five++;
                    //Reset Variables
                    four = 1;
                    loop_four = 26;
                    int length = pw.length();
                    pw[length - 4] = reset4;
                    reset4 = 'a';
                }
                six++;
                //Reset Variables
                five = 1;
                loop_five = 26;
                int length = pw.length();
                pw[length - 5] = reset5;
                reset5 = 'a';
            }
            seven++;
            //Reset Variables
            six = 1;
            loop_six = 26;
            int length = pw.length();
            pw[length - 6] = reset6;
            reset6 = 'a';
        }
        eight++;
        //Reset Variables
        seven = 1;
        loop_seven = 26;
        int length = pw.length();
        pw[length - 7] = reset7;
        reset7 = 'a';
    }

    //If password not found.
    //if(signal != 1)
    //    cout<<"Password not found."<<endl;
    return NULL;
}

/*
This functions asks the user to enter the username and returns the provided username.
*/
string get_username(){
    string user = "";
    cout<<"Enter username: ";
    cin>>user;

    return user;
}

int main(int argc, char* argv[])
{

    int myrank,nprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int alphabets = 26;
    nprocs -= 1;

    //Dividing alphabets for each slave
    int div = alphabets / nprocs;
    int rem = alphabets % nprocs;
    string s = "a";
    
    if(myrank == 0){

        //Getting hash and salt value from shadow file
        string salt1;
        string hash;
        bool flag = false;
        while(!flag){

            string username = get_username();
            ifstream ifile("shadow.txt");
            string line;
            while (ifile) {

                getline(ifile, line);
            
                if  (line.find(username) == 0){
                    int index = line.find("$", line.find("$", line.find("$") + 1) + 1);
                    salt1 = line.substr(username.length() + 1, index - username.length());
                    hash = line.substr(username.length() + 1, line.find(":", username.length() + 1) - username.length() - 1);
                    flag = true;
                    break;
                }
            }

            if (!flag){
                cout << "Username not found!" << endl;
            }
        }
        
        char* salt = str_to_char(salt1);
        char* result = str_to_char(hash);
        int salt_size = strlen(salt);
        int result_size = strlen(result);
        
        //Sending hash values over to slaves as well.
        //cout<<"\nSalt: "<<salt<<endl<<"Hash: "<<result<<endl<<endl;
        //Also sending divided alphabets for them to check.
        
        for(int i = 0; i < nprocs; i++){
            MPI_Send(&i, 1, MPI_INT, i + 1, 1234, MPI_COMM_WORLD);

            MPI_Send(&salt_size, 1, MPI_INT, i + 1, 1234, MPI_COMM_WORLD);
            MPI_Send(salt, salt_size, MPI_CHAR, i + 1, 1234, MPI_COMM_WORLD);

            MPI_Send(&result_size, 1, MPI_INT, i + 1, 1234, MPI_COMM_WORLD);
            MPI_Send(result, result_size, MPI_CHAR, i + 1, 1234, MPI_COMM_WORLD);
            
        }

        int found1 = 0;       
        //One thread checks password of remaining letters if any.
        //One thread waits for abort signal if password is found. 
        cout<<"\nSearching for Password..."<<endl;

        #pragma omp parallel num_threads(2) shared(found1, signal)
        {
            //Master Checking remaining alphabets if division is not even.
            if(omp_get_thread_num() == 0){
            
                if(rem != 0){
                    s[0] += div * nprocs;
                    //cout<<"\nMaster's Starting alphabet to Search: "<<s<<endl;
                    //cout<<"\nMaster's Total Alphabets to Search: "<<rem<<endl;

                    char *password = brute_force(salt, result, s, rem);
                    //If password found, inform all others to stop the search.
                    if (password != NULL){
                        found1 = 1;
                        int stop = 5;
                        for(int i = 0; i < nprocs; i++){
                            MPI_Send(&stop, 1, MPI_INT, i + 1, 1232, MPI_COMM_WORLD);
                        }
                    }
                }
            }
            else{

                int found2;
                //If password found, inform all others to stop the search.
                MPI_Recv(&found2, 1, MPI_INT, MPI_ANY_SOURCE, 1233, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if(found2 != 5){
                    signal = 1;
                    for(int i = 0; i < nprocs; i++){
                        MPI_Send(&found2, 1, MPI_INT, i + 1, 1232, MPI_COMM_WORLD);
                    }
                }
            }
        }
    }
    else{

        //Recieving hash, salt and divided alphabets

        int div_size;
        MPI_Recv(&div_size, 1, MPI_INT, 0, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int salt_size;
        MPI_Recv(&salt_size, 1, MPI_INT, 0, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        char* salt = new char[salt_size];
        MPI_Recv(salt, salt_size, MPI_CHAR, 0, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        salt[salt_size] = '\0';

        int result_size;
        MPI_Recv(&result_size, 1, MPI_INT, 0, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        char* result = new char[result_size];
        MPI_Recv(result, result_size, MPI_CHAR, 0, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        result[result_size] = '\0';


        #pragma omp parallel num_threads(2) shared(signal)
        {
            //Waiting for abort signal
            if(omp_get_thread_num() == 0){
                int found;
                MPI_Recv(&found, 1, MPI_INT, 0, 1232, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                //Global signal to abort remaining proccesses.
                signal = 1;
                if(found == 5){
                    int temp = 5;
                    MPI_Send(&temp, 1, MPI_INT, 0, 1233, MPI_COMM_WORLD);
                }
            }
            else{
                //Finding password on assigned alphabets
                s[0] += div * div_size;
                //sleep(myrank);
                //cout<<"\nSlave "<<myrank<<" Starting alphabet to Search: "<<s<<endl;
                //cout<<"\nSlave "<<myrank<<" Total Alphabets to Search: "<<div<<endl;
                    
                char *password = brute_force(salt, result, s, div);
                if (password != NULL){
                    int send = 1;
                    MPI_Send(&send, 1, MPI_INT, 0, 1233, MPI_COMM_WORLD);
                }
            }
        }
    }

    MPI_Finalize();
    return 0;

}
