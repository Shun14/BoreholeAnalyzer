#include <QFile>

#include "qexcel.h"

#include "qt_windows.h"

QExcel::QExcel(QObject *parent) : QObject(parent)
{
    pExcel     = NULL;
    pWorkbooks = NULL;
    pWorkbook  = NULL;
    pWorksheet = NULL;

    sXlsFile     = "";
    nRowCount    = 0;
    nColumnCount = 0;
    nStartRow    = 0;
    nStartColumn = 0;

    bIsOpen     = false;
    bIsValid    = false;
    bIsANewFile = false;
    bIsSaveAlready = false;

    HRESULT r = OleInitialize(0);
    if (r != S_OK && r != S_FALSE)
    {
        qDebug("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
    }
}

QExcel::QExcel(QString xlsFile)
{
    pExcel     = NULL;
    pWorkbooks = NULL;
    pWorkbook  = NULL;
    pWorksheet = NULL;

    sXlsFile     = xlsFile;
    nRowCount    = 0;
    nColumnCount = 0;
    nStartRow    = 0;
    nStartColumn = 0;

    bIsOpen     = false;
    bIsValid    = false;
    bIsANewFile = false;
    bIsSaveAlready = false;

    HRESULT r = OleInitialize(0);
    if (r != S_OK && r != S_FALSE)
    {
        qDebug("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
    }
}

QExcel::~QExcel()
{
    if ( bIsOpen )
    {
        //����ǰ���ȱ������ݣ�Ȼ��ر�workbook
        Close();
    }
    OleUninitialize();
}

/**
  *@brief ��sXlsFileָ����excel����
  *@return true : �򿪳ɹ�
  *        false: ��ʧ��
  */
bool QExcel::Open(UINT nSheet, bool visible)
{

    if ( bIsOpen )
    {
        //return bIsOpen;
        Close();
    }

    nCurrSheet = nSheet;
    bIsVisible = visible;

    if ( NULL == pExcel )
    {
        pExcel = new QAxObject("Excel.Application");
        if ( pExcel )
        {
            bIsValid = true;
        }
        else
        {
            bIsValid = false;
            bIsOpen  = false;
            return bIsOpen;
        }

        pExcel->dynamicCall("SetVisible(bool)", bIsVisible);
    }

    if ( !bIsValid )
    {
        bIsOpen  = false;
        return bIsOpen;
    }

    if ( sXlsFile.isEmpty() )
    {
        bIsOpen  = false;
        return bIsOpen;
    }

    /*���ָ����ļ������ڣ�����Ҫ�½�һ��*/
    QFile f(sXlsFile);
    if (!f.exists())
    {
        bIsANewFile = true;
    }
    else
    {
        bIsANewFile = false;
    }

    if (!bIsANewFile)
    {
        pWorkbooks = pExcel->querySubObject("WorkBooks"); //��ȡ������
        pWorkbook = pWorkbooks->querySubObject("Open(QString, QVariant)",sXlsFile,QVariant(0)); //��xls��Ӧ�Ĺ�����
    }
    else
    {
        pWorkbooks = pExcel->querySubObject("WorkBooks");     //��ȡ������
        pWorkbooks->dynamicCall("Add");                       //���һ���µĹ�����
        pWorkbook  = pExcel->querySubObject("ActiveWorkBook"); //�½�һ��xls
    }

    pWorksheet = pWorkbook->querySubObject("WorkSheets(int)", nCurrSheet);//�򿪵�һ��sheet

    //�����Ѵ򿪣���ʼ��ȡ��Ӧ����
    QAxObject *usedrange = pWorksheet->querySubObject("UsedRange");//��ȡ��sheet��ʹ�÷�Χ����
    QAxObject *rows = usedrange->querySubObject("Rows");
    QAxObject *columns = usedrange->querySubObject("Columns");

    //��Ϊexcel���Դ��������������ݶ���һ���Ǵ�0,0��ʼ�����Ҫ��ȡ�������±�
    nStartRow    = usedrange->property("Row").toInt();    //��һ�е���ʼλ��
    nStartColumn = usedrange->property("Column").toInt(); //��һ�е���ʼλ��

    nRowCount    = rows->property("Count").toInt();       //��ȡ����
    nColumnCount = columns->property("Count").toInt();    //��ȡ����

    bIsOpen  = true;
    return bIsOpen;
}

/**
  *@brief Open()�����غ���
  */
bool QExcel::Open(QString xlsFile, UINT nSheet, bool visible)
{
    sXlsFile = xlsFile;
    nCurrSheet = nSheet;
    bIsVisible = visible;

    return Open(nCurrSheet,bIsVisible);
}

/**
  *@brief ���������ݣ�������д���ļ�
  */
void QExcel::Save()
{
    if ( pWorkbook )
    {
        if (bIsSaveAlready)
        {
            return ;
        }

        if (!bIsANewFile)
        {
            pWorkbook->dynamicCall("Save()");
        }
        else /*������ĵ����½������ģ���ʹ�����ΪCOM�ӿ�*/
        {
            pWorkbook->dynamicCall("SaveAs (const QString&,int,const QString&,const QString&,bool,bool)",
                sXlsFile,56,QString(""),QString(""),false,false);

        }

        bIsSaveAlready = true;
    }
}


/**
  *@brief �ر�ǰ�ȱ������ݣ�Ȼ��رյ�ǰExcel COM���󣬲��ͷ��ڴ�
  */
void QExcel::Close()
{
    //�ر�ǰ�ȱ�������
    Save();

    if ( pExcel && pWorkbook )
    {
        pWorkbook->dynamicCall("Close(bool)", true);
        pExcel->dynamicCall("Quit()");

        delete pExcel;
        pExcel = NULL;

        bIsOpen     = false;
        bIsValid    = false;
        bIsANewFile = false;
        bIsSaveAlready = true;
    }
}


void QExcel::setCellString(const QString& cell, const QString& value)
{
    QAxObject *range = pWorksheet->querySubObject("Range(const QString&)", cell);
    range->dynamicCall("SetValue(const QString&)", value);
    range->setProperty("HorizontalAlignment", -4108);//xlCenter
}

void QExcel::setCellString(int row, int column, const QString& value)
{
    QAxObject *range = pWorksheet->querySubObject("Cells(int,int)", row, column);
    range->dynamicCall("SetValue(const QString&)", value);
    range->setProperty("HorizontalAlignment", -4108);//xlCenter
}

//�ϲ���Ԫ��
void QExcel::mergeCells(const QString& cell)
{
    QAxObject *range = pWorksheet->querySubObject("Range(const QString&)", cell);
    range->setProperty("VerticalAlignment", -4108);//��ֱ����
    range->setProperty("HorizontalAlignment", -4108);//ˮƽ����
    range->setProperty("WrapText", true);
    range->setProperty("MergeCells", true);
}

//�ϲ���Ԫ�����غ���
void QExcel::mergeCells(int topLeftRow, int topLeftColumn, int bottomRightRow, int bottomRightColumn)
{
    QString cell;
    cell.append(QChar(topLeftColumn - 1 + 'A'));
    cell.append(QString::number(topLeftRow));
    cell.append(":");
    cell.append(QChar(bottomRightColumn - 1 + 'A'));
    cell.append(QString::number(bottomRightRow));

    QAxObject *range = pWorksheet->querySubObject("Range(const QString&)", cell);
    range->setProperty("VerticalAlignment", -4108);//xlCenter
    range->setProperty("WrapText", true);
    range->setProperty("MergeCells", true);
}

void QExcel::setColumnWidth(int column, int width)
{
    QString columnName;
    columnName.append(QChar(column - 1 + 'A'));
    columnName.append(":");
    columnName.append(QChar(column - 1 + 'A'));

    QAxObject * col = pWorksheet->querySubObject("Columns(const QString&)", columnName);
    col->setProperty("ColumnWidth", width);
}

void QExcel::setRowHeight(int row, int height)
{
    QString rowsName;
    rowsName.append(QString::number(row));
    rowsName.append(":");
    rowsName.append(QString::number(row));

    QAxObject * r = pWorksheet->querySubObject("Rows(const QString &)", rowsName);
    r->setProperty("RowHeight", height);
}

/**
  *@brief ��ճ�����֮�������
  */
void QExcel::Clear()
{
    sXlsFile     = "";
    nRowCount    = 0;
    nColumnCount = 0;
    nStartRow    = 0;
    nStartColumn = 0;
}

/**
  *@brief �ж�excel�Ƿ��ѱ���
  *@return true : �Ѵ�
  *        false: δ��
  */
bool QExcel::IsOpen()
{
    return bIsOpen;
}

/**
  *@brief �ж�excel COM�����Ƿ���óɹ���excel�Ƿ����
  *@return true : ����
  *        false: ������
  */
bool QExcel::IsValid()
{
    return bIsValid;
}
