#include "mainwindow.h"
#include <QApplication>
#include "gtest/gtest.h"
#include "../../matrix.h"

class MatrixTest : public ::testing::Test
{
  MatrixTest()                             // You can do set-up work for each test here.
  {
  }

  virtual ~MatrixTest()                    // You can do clean-up work that doesn't throw exceptions here.
  {
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp()                  // Code here will be called immediately after the constructor (right before each test)
  {
  }

  virtual void TearDown()               // Code here will be called immediately after each test (right before the destructor)
  {
  }

  // Objects declared here can be used by all tests in the test case for Foo.

};


TEST(MatrixTest, Check_1Param)
{
  QString TestName = "Test Matrix name" ;
  uint Testrows =8;
  uint TestCols = 8 ;
  quint32 TestColors = 3 ;

  MathMatrix* TestMatrix ;

  TestMatrix = new MathMatrix(TestName,TestCols,Testrows,TestColors);
  EXPECT_EQ( TestMatrix->getName() , TestName);
  delete TestMatrix;
}

TEST(MatrixTest, Check_2Params)
{
  QString TestName = "Test Matrix name" ;
  uint Testrows =8;
  uint TestCols = 8 ;
  quint32 TestColors = 3 ;

  MathMatrix* TestMatrix ;
  TestMatrix = new MathMatrix(TestName,TestCols,Testrows);
  EXPECT_EQ( TestMatrix->getName() , TestName);
  EXPECT_EQ( TestMatrix->getColors() , TestColors);
  delete TestMatrix;
}

TEST(MatrixTest, Check_3Params)
{
  QString TestName = "Test Matrix name" ;
  uint Testrows =8;
  uint TestCols = 8 ;
  quint32 TestColors = 3 ;

  MathMatrix* TestMatrix ;
  TestMatrix = new MathMatrix(TestName,TestCols);
  EXPECT_EQ( TestMatrix->getName() , TestName);
  EXPECT_EQ( TestMatrix->getRows() , Testrows);
  EXPECT_EQ( TestMatrix->getColors() , TestColors);
  delete TestMatrix;
}

TEST(MatrixTest, Check_AllParams)
{
  QString TestName = "Test Matrix name" ;
  uint Testrows =8;
  uint TestCols = 8 ;
  quint32 TestColors = 3 ;

  MathMatrix* TestMatrix ;
  TestMatrix = new MathMatrix(TestName);
  EXPECT_EQ( TestMatrix->getName() , TestName);
  EXPECT_EQ( TestMatrix->getCols() , TestCols);
  EXPECT_EQ( TestMatrix->getRows() , Testrows);
  EXPECT_EQ( TestMatrix->getColors() , TestColors);
  delete TestMatrix;
}


TEST(MatrixTest, Check_Good_RowsRange)
{
    uint TestRows = 8 ;
    MathMatrix* TestMatrix ;

    TestMatrix = new MathMatrix("TestName",8,TestRows,3);
    for ( uint i =0; i<TestRows;++i)
        EXPECT_EQ( TestMatrix->Check_ColRange(i) , true);
    delete TestMatrix;
}

TEST(MatrixTest, Check_Bad_RowsRange)
{
    uint TestRows = 8 ;
    MathMatrix* TestMatrix ;

    // Checking negative bad colrange
    TestMatrix = new MathMatrix("TestName",8,TestRows,3);
    for (int i =-10; i<0;++i)
        EXPECT_EQ( TestMatrix->Check_ColRange(i) , false);
    delete TestMatrix;

    // Checking positive bad colrange
    TestMatrix = new MathMatrix("TestName",8,TestRows,3);
    for (int i =TestRows; i>20;++i)
        EXPECT_EQ( TestMatrix->Check_ColRange(i) , false);
    delete TestMatrix;
}

TEST(MatrixTest, Check_Good_ColsRange)
{
    uint TestCols = 8 ;
    MathMatrix* TestMatrix ;

    TestMatrix = new MathMatrix("TestName",TestCols,8,3);
    for ( uint i =0; i<TestCols;++i)
        EXPECT_EQ( TestMatrix->Check_RowRange(i) , true);
    delete TestMatrix;
}

TEST(MatrixTest, Check_Bad_ColsRange)
{
    uint TestCols = 8 ;
    MathMatrix* TestMatrix ;

    // Checking negative bad col range
    TestMatrix = new MathMatrix("TestName",TestCols,8,3);
    for (int i =-10; i<0;++i)
        EXPECT_EQ( TestMatrix->Check_RowRange(i) , false);
    delete TestMatrix;

    // Checking positive bad Cols range
    TestMatrix = new MathMatrix("TestName",TestCols,8,3);
    for (int i =TestCols; i>20;++i)
        EXPECT_EQ( TestMatrix->Check_RowRange(i) , false);
    delete TestMatrix;
}

TEST(MatrixTest, Check_Good_Ranges)
{
    uint TestRows = 8 ;
    uint TestCols = 8 ;
    MathMatrix* TestMatrix ;

    TestMatrix = new MathMatrix("TestName",TestRows,TestCols,3);
    for ( uint i =0; i<TestRows;++i)
        for ( uint j =0; j<TestCols;++j)
        EXPECT_EQ( TestMatrix->CheckRanges(i,j) , true);
    delete TestMatrix;


}

TEST(MatrixTest, Check_Bad_Ranges)
{
    uint TestRows = 8 ;
    uint TestCols = 8 ;
    MathMatrix* TestMatrix ;

    // Checking bad Cols ranges
    TestMatrix = new MathMatrix("TestName",TestRows,TestCols,3);
    for (int i =-10; i<0;++i)
        for ( uint j =0; j<TestCols;++j)
        EXPECT_EQ( TestMatrix->CheckRanges(i,j) , false);
    delete TestMatrix;

    // Checking bad Rows ranges
    TestMatrix = new MathMatrix("TestName",TestRows,TestCols,3);
   for ( uint i =0; i<TestCols;++i)
        for ( uint j =TestRows; j>20;++j)
        {
            EXPECT_EQ( TestMatrix->CheckRanges(i,j) , false);
        }
    delete TestMatrix;

    // Checking bad both ranges
    TestMatrix = new MathMatrix("TestName",TestRows,TestCols,3);
    for (int i =-10; i<0;++i)
        for ( uint j =TestRows; j>20;++j)
        {
            EXPECT_EQ( TestMatrix->CheckRanges(i,j) , false);
        }
    delete TestMatrix;
}

TEST(MatrixTest, Check_Fill)
{
    uint TestRows = 8 ;
    uint TestCols = 8 ;
    QRgb TestFill = 0x00000001 ;
    QRgb AlphaVal = 0xFF000000 ;
    MathMatrix* TestMatrix ;

    TestMatrix = new MathMatrix("TestName",TestCols,TestRows,3);
    TestMatrix->Fill(TestFill) ;
    for ( uint i =0; i<TestCols; ++i)
        for ( uint j =0; j<TestRows;++j)
        {
            EXPECT_EQ(  TestMatrix-> GetPoint(i,j), TestFill +AlphaVal ) ;
        }
    delete TestMatrix;
}


TEST(MatrixTest, Check_SetLine)
{
    uint TestColor = 0xFF000001 ;
    uint TestRows = 8 ;

    MathMatrix* TestMatrix ;

    TestMatrix = new MathMatrix("TestName",8,8,3);
    TestMatrix->SetLine(1,TestColor) ;
    for ( uint i =0; i<TestRows; ++i)
        EXPECT_EQ( TestMatrix->GetPoint(1,i) , TestColor);

    delete TestMatrix;
}

TEST(MatrixTest, Check_SetColumn)
{
    uint TestColor = 0xFF000001 ;
    uint TestCols = 8 ;

    MathMatrix* TestMatrix ;

    TestMatrix = new MathMatrix("TestName",8,8,3);
    TestMatrix->SetColumn(1,TestColor) ;
    for ( uint i =0; i<TestCols; ++i)
        EXPECT_EQ( TestMatrix->GetPoint(i,1) , TestColor);

    delete TestMatrix;
}

TEST(MatrixTest, Check_SetBorder)
{
    uint TestColor = 0xFF000001 ;
    uint TestCols = 8 ;
    uint TestRows = 8 ;

    MathMatrix* TestMatrix ;

    TestMatrix = new MathMatrix("TestName",8,8,3);
    TestMatrix->SetBorder(TestColor) ;
    for ( uint i =0; i<TestRows; ++i)
    {
        EXPECT_EQ( TestMatrix->GetPoint(0,i) , TestColor);
        EXPECT_EQ( TestMatrix->GetPoint( (TestRows-1) ,i ) , TestColor);
    }

    for ( uint i =0; i<TestCols; ++i)
    {
        EXPECT_EQ( TestMatrix->GetPoint(i,0) , TestColor);
        EXPECT_EQ( TestMatrix->GetPoint( i,(TestCols-1) ) , TestColor);
    }

    delete TestMatrix;
}

TEST(MatrixTest, Check_LineShift)
{
    uint TestRows = 8 ;
    uint TestColor = 0xFF000001 ;
    MathMatrix* TestMatrix ;

    TestMatrix = new MathMatrix("TestName",8,8,3);
    TestMatrix->SetLine(1,TestColor) ;
    TestMatrix->LineShift(1);
    for ( uint i =0; i<TestRows; ++i)
        EXPECT_EQ( TestMatrix->GetPoint(2,i) , TestColor);

    delete TestMatrix;
}

TEST(MatrixTest, Check_ColShift)
{
    uint TestCols = 8 ;
    uint TestColor = 0xFF000001 ;
    MathMatrix* TestMatrix ;

    TestMatrix = new MathMatrix("TestName",8,8,3);
    TestMatrix->SetColumn(1,TestColor) ;
    TestMatrix->ColShift(1);
    for ( uint i =0; i<TestCols; ++i)
        EXPECT_EQ( TestMatrix->GetPoint(i,2) , TestColor);

    delete TestMatrix;
}

/*
TEST(MatrixTest, Check_)
{
    MathMatrix* TestMatrix ;

    TestMatrix = new MathMatrix("TestName",8,8,3);
    EXPECT_EQ( TestMatrix->getColors() , TestColors);
    delete TestMatrix;
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testing::InitGoogleTest( &argc,argv);
    RUN_ALL_TESTS() ;

//    MainWindow w;
//    w.show();

    return a.exec();
}
