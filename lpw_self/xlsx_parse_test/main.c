
#include "stdio.h"
#include "libxl.h"

int main()
{
    BookHandle in_book = NULL;
    BookHandle out_book = NULL;
    SheetHandle in_book_sheet0 = NULL;
    SheetHandle out_book_sheet0 = NULL;
    FormatHandle string_format = NULL;
    FormatHandle num_format = NULL;
    FormatHandle empty_format = NULL;
    FormatHandle blank_format = NULL;
    FontHandle font = NULL;
    int first_col = 0;
    int first_row = 0;
    int last_col = 0;
    int last_row = 0;
    int i = 0;
    int j = 0;
    int cell_type = -1;

    //建xlsx格式的Handle
    in_book = xlCreateXMLBook();
    if(!in_book)
    {
        return -1;
    }
    out_book = xlCreateXMLBook();
    if(!out_book)
    {
        return -1;
    }
    //Load数据
    if(!xlBookLoad(in_book,"test.xlsx"))
    {
        return -1;
    }
    //从book handle中取第一张表handle
    in_book_sheet0=xlBookGetSheet(in_book,0);
    //后续判断handle是否为空就不加了,懒
    
    //以同名的方式在输出xlsx中加入一张Sheet
    out_book_sheet0 = xlBookAddSheet(out_book,xlSheetName(in_book_sheet0),NULL);
    first_col = xlSheetFirstCol(in_book_sheet0);
    first_row = xlSheetFirstRow(in_book_sheet0);
    last_col = xlSheetLastCol(in_book_sheet0);
    last_row = xlSheetLastRow(in_book_sheet0);

    //add font
    font = xlBookAddFont(out_book,0);
    
    xlFontSetColor(font,COLOR_RED);
    xlFontSetSize(font,36);
    //add format
    string_format = xlBookAddFormat(out_book,NULL);
    num_format = xlBookAddFormat(out_book,NULL);
    empty_format = xlBookAddFormat(out_book,NULL);
    blank_format = xlBookAddFormat(out_book,NULL);

    xlFormatSetFont(string_format,font);
    xlFormatSetAlignH(num_format,ALIGNH_CENTER);
    xlFormatSetAlignV(num_format,ALIGNV_CENTER);

    //xlFormatSetBorderColor(num_format,COLOR_BLUE);
    for(i=first_row;i<last_row-first_row;i++)
    {
        for(j=first_col;j<last_col-first_col;j++)
        {
            //获取单元格数据类型,根据不同的数据类型调用不同的函数
            cell_type= xlSheetCellType(in_book_sheet0,i,j);
            printf("%d %d cell type is %d\n",i,j,cell_type);
            switch(cell_type)
            {
            case CELLTYPE_STRING:
                xlSheetWriteStr(out_book_sheet0,i,j,xlSheetReadStr(in_book_sheet0,i,j,0),string_format);
                break;

            case CELLTYPE_NUMBER:
                xlSheetWriteNum(out_book_sheet0,i,j,xlSheetReadNum(in_book_sheet0,i,j,0),num_format);
                break;

            case CELLTYPE_BLANK:
                xlSheetWriteBlank(out_book_sheet0,i,j,blank_format);
                break;

            default:
                //do nothing
                break;
            }
        }
    }
    //合并单元格
    //xlSheetSetMerge(out_book_sheet0,0,1,0,0);
    //自适应单元格大小
    xlSheetSetAutoFitArea(out_book_sheet0,first_row,first_col,last_row,last_col);

    //保存文件
    xlBookSave(out_book,"test_out.xlsx");
    //释放
    if(!in_book)
    {
        xlBookRelease(in_book);
    }
    if(!out_book)
    {
        xlBookRelease(out_book);
    }
    return 0;
}
