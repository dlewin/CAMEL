#include "mainwindow.h"
#include <QApplication>
#include "gtest/gtest.h"
#include "../../matrix.h"

/*
bool IsPrime(int n)
{
    // Trivial case 1: small numbers
    if (n <= 1) return false;

    // Trivial case 2: even numbers
    if (n % 2 == 0) return n == 2;

    // Now, we have that n is odd and n >= 3.

    // Try to divide n by every odd number i, starting from 3
    for (int i = 3; ; i += 2) {
        // We only have to try i up to the squre root of n
        if (i > n/i) break;

        // Now, we have i <= n/i < n.
        // If n is divisible by i, n is not prime.
        if (n % i == 0) return false;
    }
    // n has no integer factor in the range (1, n), and thus is prime.
    return true;
}
class IsPrimeParamTest : public::testing::TestWithParam<int>
{

};
TEST_P(IsPrimeParamTest, HandleTrueReturn)
{
    int n =  GetParam();
    EXPECT_TRUE(IsPrime(n));
}
INSTANTIATE_TEST_CASE_P(TrueReturn, IsPrimeParamTest, testing::Values(3, 5, 11, 23, 17));
*/

class MatrixTest : public ::testing::Test
{

  //MathMatrix *TestMatrix(const QString , const quint16 , const quint16 , const quint32 ); ;
  MatrixTest()                             // You can do set-up work for each test here.
  {

  }

  virtual ~MatrixTest()                    // You can do clean-up work that doesn't throw exceptions here.
  { }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp()                  // Code here will be called immediately after the constructor (right before each test)
  {

  }

  virtual void TearDown()               // Code here will be called immediately after each test (right before the destructor)
  {   }

  // Objects declared here can be used by all tests in the test case for Foo.

};


TEST(MatrixTest, Check_ColRange)
{
  MathMatrix TestMatrix("Test Matrix name",8,8,83);
    //TestMatrix.SetColumn(1,"orange");
  EXPECT_EQ(TestMatrix.getName() , "Test Matrix name");
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testing::InitGoogleTest( &argc,argv);
    RUN_ALL_TESTS() ;

//    MainWindow w;
//    w.show();

    return a.exec();
}
