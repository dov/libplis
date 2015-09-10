#include <math.h>
#include <stdio.h>
#include <string.h>
#include <plis.h>
#include <fstream>

using namespace plis;

bool test_ok(bool is_ok,
             int test_number);

static int num_tests = 0;

int main()
{
    int count_ok = 0;
    slip S_, s1, s2;

    /* Simple assignment and equiv with string */
    S_ = "abc";
    count_ok += test_ok(S_ == "abc",                                1);
    count_ok += test_ok(!(S_ == "def"),                             2);
    count_ok += test_ok(S_ != "def",                                3);
    count_ok += test_ok(!(S_ != "abc"),                             4);
                                                                    
    /* slip equal operator */                                       
    s1 = "abc";                                                     
    count_ok += test_ok(S_ == s1,                                   5);
    count_ok += test_ok(!(S_ != s1),                                6);
    s1 = "def";                                                     
    count_ok += test_ok(!(S_ == s1),                                7);
    count_ok += test_ok(S_ != s1,                                   8);
                                                                    
    /* Comparisons */                                               
    count_ok += test_ok(S_ < s1,                                    9);
    count_ok += test_ok(!(S_ > s1),                                 10);
                                                                    
    /* chop operator */                                             
    S_.chop();                                                      
    count_ok += test_ok(S_ == "ab",                                 11);
                                                                    
    /* tr operator */                                               
    S_.tr("a","A");                                                 
    count_ok += test_ok(S_ == "Ab",                                 12);

    /* atof and atoi operators */
    S_ = "34.5";
    count_ok += test_ok(S_.atoi() == 34 && S_.atof() == 34.5,       13);
    
    /* slip lists */
    llip Q_, Qa;
    S_ = "the quick brown fox";
    Q_ = S_.split();
    /* Length in scalar contents */
    count_ok += test_ok(Q_ == 4,                                    14);
    count_ok += test_ok(Q_[0] == "the",                             15);
    count_ok += test_ok(Q_[3] == "fox",                             16);
                                                                    
    /* Empty split should return an empty list. */                  
    S_ = " ";                                                       
    count_ok += test_ok(S_.split() == 0,                            17);
    /* Awk splitting */                                             
    count_ok += test_ok(S_.split("' '") == 0,                       18);
 
    /* join operator */
    count_ok += test_ok(Q_.join(",") == "the,quick,brown,fox",      19);

    /* Regular expressions */
    S_ = "The Quick Brown Fox";
    count_ok += test_ok(S_.m("quick", "i") == 1,                    20);
    count_ok += test_ok(S_.m("quick") == 0,                         21);

    /* Match the word "brown" through a complex non-greedy match */
    int ret = S_.m("\\bb.*?\\b", Q_, "i");
    count_ok += test_ok(ret == 1 && Q_[0] == "Brown",               22);

    /* Test assignment to groups */
    ret = S_.m("Q\\w*\\s+(\\w+)", Q_);
    count_ok += test_ok(ret == 2 && Q_[1] == "Brown",               23);

    /* Regular expression change */
    S_.s("[A-Z]", "*$&*", "g");
    count_ok += test_ok(S_ == "*T*he *Q*uick *B*rown *F*ox",        24);
    S_.s("\\*.*?\\*", "-");
    count_ok += test_ok(S_ == "-he *Q*uick *B*rown *F*ox",          25);
    S_.s("\\*.*\\*", "-");
    count_ok += test_ok(S_ == "-he -ox",                            26);
    
    /* White space split */
    S_ = "a b\r\n\t \nc";
    S_.wsplit(Q_);
    count_ok += test_ok(Q_.join(",") == "a,b,c",                    27);

    /* Push and shift operators */
    S_ = "quick brown";
    Q_ = S_.split();
    Q_.unshift("The");
    Q_.push("fox");
    count_ok += test_ok(Q_.join() == "The quick brown fox",         28);
    count_ok += test_ok(Q_.pop() == "fox",                          29);
    count_ok += test_ok(Q_.shift() == "The",                        30);
    count_ok += test_ok(Q_.join() == "quick brown",                 31);

    /* Joining of lists through the push and unshift operators. */
    Q_ = ((slip)"The quick").split();
    Qa = ((slip)"brown fox").split();
    Q_.push(Qa);
    count_ok += test_ok(Q_.join() == "The quick brown fox",         32);
    Q_.pop();
    Q_.pop();
    Q_.unshift(Qa);
    count_ok += test_ok(Q_.join() == "brown fox The quick",         33);
                                   
    /* Substr extraction and assignment */
    S_ = "The qk brown fox";
    count_ok += test_ok((slip)S_.substr(4,2) == "qk",               34);
    S_.substr(4,2) = "*QUICK*";
    count_ok += test_ok(S_ == "The *QUICK* brown fox",              35);

    /* Test whilep on a file */
    std::fstream filestr;
    filestr.open ("test-plis.txt", std::fstream::out);
    filestr << (slip)"The quick\n";
    filestr << (slip)"brown fox\n";
    filestr.close();

    filestr.open ("test-plis.txt", std::fstream::in);
    slip files;
    int lineno=1;
    while(filestr >> S_)
	files+= slipprintf("%d: ", lineno++) + S_;
    filestr.close();
    count_ok += test_ok(files == "1: The quick\n2: brown fox\n",    36);

    /* Tests that crashed at one point or another */
    S_ = "the\nquick\n";
    S_.s("^","  ","gm");
    count_ok += test_ok(S_ == "  the\n  quick\n  ",                 37);
    

    /* Testing reading of a file */
    {
        FILE *test_file = fopen("test.txt", "w");
        count_ok += test_ok(test_file != NULL,                      36);
        if (test_file != NULL) {
            // This currently fails unless the string ends with a \n
            slip stest = "The quick\nBrown\nFox\n";
            fprintf(test_file, "%s", stest.c_str());
            fclose(test_file);

            S_.chomp();
            
            if (slip_read_file("test.txt", S_) == 0) 
                count_ok += test_ok(S_ == stest,                    37);
        }

        count_ok += test_ok(slip_read_file("nosuchfile", S_) != 0,  38);
    }

    // C++11 operators
    {
        S_ = "the quick brown fox";
        llip Q_ = S_.split();

        slip jj;
        for (auto& s : Q_)
          jj += s;
      
        count_ok += test_ok(jj=="thequickbrownfox",                39);

        // Initializer list.
        llip Q1_ { "the", "quick", "brown", "fox" };
        count_ok += test_ok(slip("").join(Q1_,",")== "the,quick,brown,fox",     40);
    }

    /*======================================================================
    //  End of tests. Create summary.
    //----------------------------------------------------------------------*/
    int count_failed = num_tests-count_ok;

    if (count_failed == 0)
        printf("All tests passed. :-)\n");
    else
        printf("%d out of %d tests failed.\n", num_tests-count_ok, num_tests);

    if (count_failed == 0)
        exit(0);
    else
        exit(-1);
}

bool test_ok(bool is_ok,
             int test_number)
{
    if (is_ok)
        printf("Passed %d\n", test_number);
    else
        printf("Failed %d\n", test_number);

    num_tests++;
    return is_ok;
}
