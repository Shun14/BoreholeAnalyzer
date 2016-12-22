#ifndef QEXCEL_H
#define QEXCEL_H

#include <QObject>
#include <QAxObject>

typedef unsigned int UINT;

class QExcel : public QObject
{
    Q_OBJECT
public:
    explicit QExcel(QObject *parent = 0);
    QExcel(QString xlsFile);
    ~QExcel();

public:
    bool Open(UINT nSheet = 1, bool visible = false);//��xls�ļ�
    bool Open(QString xlsFile, UINT nSheet = 1, bool visible = false);
    void Save();                //����xls����
    void Close();               //�ر�xls����

    void setCellString(const QString& cell, const QString& value);
    void setCellString(int row, int column, const QString& value);
    void mergeCells(const QString& cell);
    void mergeCells(int topLeftRow, int topLeftColumn, int bottomRightRow, int bottomRightColumn);
    void setColumnWidth(int column, int width);
    void setRowHeight(int row, int height);

    bool IsOpen();
    bool IsValid();

protected:
    void Clear();

private:
    QAxObject *pExcel;      //ָ������excelӦ�ó���
    QAxObject *pWorkbooks;  //ָ��������,excel�кܶ๤����
    QAxObject *pWorkbook;   //ָ��sXlsFile��Ӧ�Ĺ�����
    QAxObject *pWorksheet;  //ָ�������е�ĳ��sheet��

    QString   sXlsFile;     //xls�ļ�·��
    UINT      nCurrSheet;   //��ǰ�򿪵ĵڼ���sheet
    bool      bIsVisible;   //excel�Ƿ�ɼ�
    int       nRowCount;    //����
    int       nColumnCount; //����
    int       nStartRow;    //��ʼ�����ݵ����±�ֵ
    int       nStartColumn; //��ʼ�����ݵ����±�ֵ

    bool      bIsOpen;      //�Ƿ��Ѵ�
    bool      bIsValid;     //�Ƿ���Ч
    bool      bIsANewFile;  //�Ƿ���һ���½�xls�ļ����������ִ򿪵�excel���Ѵ����ļ������б����½���
    bool      bIsSaveAlready;//��ֹ�ظ�����

signals:

public slots:
};

#endif // QEXCEL_H
