#include <stdio.h>
#include <string.h>

//問題の正解状況を登録する
int add_point_data()
{
    char file_name[256];

    FILE *fp;
    //ファイル名の入力
    while (1)
    {
        printf("結果を記述するファイル名を入力：");
        scanf("%s", file_name);
        fp = fopen(file_name, "w");
        if (fp == NULL)
        {
            printf("ファイルが作れないよ！！！\n正しいファイル名を入れてください！！");
        }
        else
        {
            break;
        }
    }
    char str[256];  //入力用
    int mondai_num; //問題数
    int n;          //人数

    //問題数と人数を入れる
    printf("まずは、問題数と人数を入力してください。例）10問20人なら、10 20　と入力します。\n");
    printf("入力：");

    scanf("%d%d", &mondai_num, &n);

    fprintf(fp, "%d %d\n", mondai_num, n);

    int i, j; //ループ用（i:人,j:問題）

    //全員分の問題の正解状況を記録する
    printf("１人ずつ問題の正解状況を入力します。\n");
    for (i = 0; i < n; i++)
    {
        printf("%2d人目の成績を入力します。\n", i + 1);
        int correct_ans[mondai_num]; //各問題の正解状況を格納する（正解なら1,不正解なら0）
        for (j = 0; j < mondai_num; j++)
        {
            printf("  %2d問目：", j + 1);
            scanf("%d", &correct_ans[j]);
        }
        printf("%2d人目の入力はここまでです。\n\n", i + 1);

        for (j = 0; j < mondai_num; j++)
        {
            if (j == 0)
                fprintf(fp, "%d", correct_ans[j]);
            else
                fprintf(fp, " %d", correct_ans[j]);
        }
        fprintf(fp, "\n");
    }

    printf("\nこれで入力を終了します。お疲れ様です。\n\n");

    fclose(fp);

    return 0;
}

//正解状況の分布を作成する
void create_bunpu()
{
    char file_name[256];
    fgets(file_name, sizeof(file_name), stdin);

    FILE *fp;
    //ファイル名の入力
    while (1)
    {
        printf("集計する結果のファイル名を入力：");
        scanf("%s", file_name);
        fp = fopen(file_name, "r");
        if (fp == NULL)
        {
            printf("ファイルが見つからないよ！！！\n正しいファイル名を入れてください！！");
        }
        else
        {
            break;
        }
    }

    //まずは難問あって何人分なのか？
    int mondai_num; //問題数
    int n;

    fscanf(fp, "%d%d", &mondai_num, &n);

    int seikai_count[mondai_num];

    int i, j; //ループ用(i:人,j:問題)

    //全ての問題の正解人数を0にセット
    for (j = 0; j < mondai_num; j++)
    {
        seikai_count[j] = 0;
    }

    int result; //正解か不正解かを読み取る

    //順番に一人一人が正解なのかを読み取り、問題ごとの正解人数を集計
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < mondai_num; j++)
        {
            fscanf(fp, "%d", &result);
            if (result == 1)
            {                      //正解なら
                seikai_count[j]++; //正解人数をカウントアップ
            }
        }
    }

    //最も点数の低い・高い問題は何か
    int min_idx = 0;
    int min = seikai_count[0];
    int max_idx = 0;
    int max = seikai_count[0];

    for (j = 0; j < mondai_num; j++)
    {
        if (min > seikai_count[j])
        {
            min = seikai_count[j];
            min_idx = j;
        }
        if (max < seikai_count[j])
        {
            max = seikai_count[j];
            max_idx = j;
        }
    }

    //画面に出力するか、ファイルに出力するかを選ばせる
    printf("分析結果はどちらに出力しますか？==========\n");
    printf("0: 画面に出力します。結果はこのプロンプト上に表示されます。\n");
    printf("1: ファイルに出力します。結果はファイルで共有できます。\n");
    int which_print; //どちらに出力するかを格納
    //ファイル名の入力
    while (1)
    {
        printf("入力：");
        scanf("%d", &which_print);
        if ((which_print == 0) || (which_print == 1))
        {
            break;
        }
        else
        {
            printf("0か1のどちらかを入力してください！！\n");
        }
    }
    printf("\n");

    if (which_print == 0)
    {
        //正統数を画面に順番に表示
        int star; //星の数を制御するループ用
        char title[256];
        printf("タイトルを入力：");
        scanf("%s", title);
        printf("\n");
        printf("タイトル：%s\n", title);
        printf("＜集計結果＞\n\n");
        for (j = 0; j < mondai_num; j++)
        {
            printf("問題%2d: ", j + 1);
            for (star = 0; star < seikai_count[j]; star++)
            {
                printf("*");
            }
            printf("\n");
        }
        printf("集計人数：%d人\n", n);
        printf("\n＜分析結果＞\n");
        printf("最も出来が良い問題：問題%d　正解率%3.1f％\n", max_idx + 1, ((double)max / n) * 100);
        printf("最も出来が悪い問題：問題%d　正解率%3.1f％\n", min_idx + 1, ((double)min / n) * 100);
    }
    else
    {
        //保存するファイルを指定する
        char file_name[256];

        FILE *fp2;
        //ファイル名の入力
        while (1)
        {
            printf("結果を出力するファイル名を入力：");
            scanf("%s", file_name);
            fp2 = fopen(file_name, "w");
            if (fp2 == NULL)
            {
                printf("ファイルが作れないよ！！！\n正しいファイル名を入れてください！！");
            }else{
                break;
            }
        }
        char title[256];
        printf("タイトルを入力：");
        scanf("%s", title);
        fprintf(fp2, "タイトル：%s\n", title);

        //正統数を画面に順番に表示
        int star; //星の数を制御するループ用
        fprintf(fp2, "＜集計結果＞\n\n");
        for (j = 0; j < mondai_num; j++)
        {
            fprintf(fp2, "問題%2d: ", j + 1);
            for (star = 0; star < seikai_count[j]; star++)
            {
                fprintf(fp2, "*");
            }
            fprintf(fp2, "\n");
        }
        fprintf(fp2, "集計人数：%d人\n", n);

        fprintf(fp2, "\n＜分析結果＞\n");
        fprintf(fp2, "最も出来が良い問題：問題%d　正解率%3.1f％\n", max_idx + 1, ((double)max / n) * 100);
        fprintf(fp2, "最も出来が悪い問題：問題%d　正解率%3.1f％\n", min_idx + 1, ((double)min / n) * 100);
        fprintf(fp2, "\n＜コメント欄＞\n\n");
        fprintf(fp2, "The output is complete.\n");

        fclose(fp2);
    }
    printf("\n集計が完了しました。\n\n");
    fclose(fp);
}

int main(void)
{
    //メニューの表示
    while (1)
    {
        printf("========C言語小テスト分布作成システム ver1.0 =============\n");
        printf("0: 得点の登録\n");
        printf("1: 結果の集計・分布の作成（すでに得点が登録されている場合はこちら）\n");
        printf("-1: 終了\n\n");

        int menu_select; //利用するメニュー

        //メニュー番号
        printf("何をしますか？（数字を入力）：　");
        scanf("%d", &menu_select);
        printf("\n");

        switch (menu_select)
        {
        case 0:
            add_point_data(); //得点データ追加機能
            break;
        case 1:
            create_bunpu(); //得点データから得点分布を作成
            break;
        case -1:
            break;
        default:
            printf("上記に載っているメニュー番号を入れてください！！\n");
            break;
        }

        //終了する
        if (menu_select == -1)
        {
            break;
        }
    }

    printf("終了します。GoodBye!!\n");

    return 0;
}