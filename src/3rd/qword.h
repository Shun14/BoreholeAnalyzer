#ifndef QWORD_H
#define QWORD_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QAxObject>
#include <QAxWidget>

class QWord : public QObject
{
    Q_OBJECT

public:
    QWord(QObject *parent = 0);
    ~QWord();

public:
    QAxObject* getDocuments(){return m_documents;}
    QAxObject* getDocument(){return m_document;}
    QAxObject* getWordApp(){return m_word;}

    //���word�İ汾��
    QString GetWordVersion();
public:
    /**************************************************************************/
    /* �ļ�   ����                                                            */
    /**************************************************************************/
    //�����������
    void save();
    //�ر� �˳� ����ʱ��Ҳ���Զ�����һ��
    void close();
    //�½�Word���Ϊ
    void saveAs();
    //����һ���µ�Word
    bool createNewWord();
    //��һ�����е�Word
    void openWord();
    //����һ���µ�Word
    bool createNewWord(const QString& filePath );

    /**************************************************************************/
    /* ����                                                            */
    /**************************************************************************/
    //����Զ������� 0�̶�  1�������ݵ���  2 ���ݴ��ڵ���
    void setTableAutoFitBehavior(int flag);
    //����ҳ��0Ϊ����wdOrientPortrait  1Ϊ����wdOrientLandscape
    void setPageOrientation(int flag);
    //����ҳ����ͼ����web��ͼwdWebView 6����ҳ����ͼwdPrintView 3 �����Ķ���ͼwdReadingView 7
    void setWordPageView(int flag);
    //���������С
    void setFontSize(int fontsize);
    //��������	���� �����塱
    void setFontName(QString& fontName);
    //����Ӵ�
    void setFontBold(bool flag);
    //����ѡ��λ�����־��� 0 ,���� 1,���� 2
    void setParagraphAlignment(int flag);
    //�����п�
    void setColumnWidth(int column, int width);
    //���õ�Ԫ���ı�
    void setCellString(int row, int column, const QString& text);
    //���õ�Ԫ���������ݴ���  isBold�����Ƿ����
    void setCellFontBold(int row, int column, bool isBold);
    //���õ�Ԫ�����ִ�С
    void setCellFontSize(int row, int column, int size);
    //�������ĵ�ƴд���  true�������  false ȡ�����
    void setOptionCheckSpell(bool flags);

    //��ȡ����
    QString GetText();
    void getUsedRange(int *topLeftRow, int *topLeftColumn, int *bottomRightRow, int *bottomRightColumn);
    //"SetRange(1, 9)"��1���ַ���ʼ������9���ַ�������Χ
    void setSelectionRange(int start,int end);
    //��ȡ��Ԫ������
    QVariant getCellValue(int row, int column);
    //��ȡword�б������
    int getTableCount();


    //��ȡ�����г��ֵĴ�����Ϣ������QMessageBox::information��ӡ ��cpp����QMessageBox �����������߳��е���������
    QString getStrErrorInfo(){return m_strError;}
    //ɾ��ָ������
    void deleteSelectColumn(int column);
    //�ƶ�ѡ�������ĵ�ĩβ
    void moveForEnd();

    //��Ԫ�����ͼƬ
    void insertCellPic(int row,int column,const QString& picPath);
    //����һ�����м��б��
    void intsertTable(int row,int column);
    //����س�
    void insertMoveDown();
    //��������
    void insertText(const QString& text);

    void insertPic(QString& picPath);
    void setMargin(int top, int bottom, int left, int right);

private:
    QAxObject* m_word;
    QAxObject* m_documents;
    QAxObject* m_document;
    QString  m_fileName;
    QString  m_saveName;
    QString  m_strError;

};

#endif // QWORD_H
