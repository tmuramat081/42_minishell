//export: 環境変数やシェル変数を設定、リスト表示するコマンド
//環境変数はグローバル変数
//書式: export [option] [変数名[=値]...]
//option:	-f シェル関数を参照
//			-n 指定した環境変数を削除しシェル変数に変える
//			-p 全てのexportされた変数と関数を一覧表示(変数名指定不可)
//mainの第3引数で環境変数を取り、printfでループを回すやり方はどうか?
//2次元配列
/*
#include <libc.h>

static void		showenv(void *env)
{
	ft_putstr_fd("declare -x ", FD_STDOUT);
	ft_putstr_fd(((t_keyval *)env)->key, FD_STDOUT);
	ft_putstr_fd("=\"", FD_STDOUT);
	ft_putstr_fd(((t_keyval *)env)->val, FD_STDOUT);
	ft_putstr_fd("\"\n", FD_STDOUT);
}

static int		sort_and_show_env(t_list *envlst)
{
	t_list		*envlst_cp;

	envlst_cp = envlst;
	if (!(envlst_cp = ft_lstdup(envlst, msh_keyval_dup, msh_keyval_free)))
		return (msh_puterr(MSH_NAME, "export", 1));
	ft_lstsort(&envlst_cp, msh_env_cmpkey);
	ft_lstiter(envlst_cp, showenv);
	ft_lstclear(&envlst_cp, msh_keyval_free);
	return (0);
}

int				main(t_mshinfo *mshinfo, char **argv, int flg_forked)
{
	int		ret;

	if (!argv || !argv[0])
		ret = 1;
	else if (!argv[1])
		ret = sort_and_show_env(mshinfo->envlst);
	else
		ret = msh_export_new_env(mshinfo, argv);
	if (flg_forked)
		exit(ret);
	mshinfo->ret_last_cmd = ret;
	return (0);
}
*/
//insert関数
//find関数
//をapiとして使う

//iterator関数: 繰り返し