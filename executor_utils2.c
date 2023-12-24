/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:15:58 by baer              #+#    #+#             */
/*   Updated: 2023/12/23 21:45:55 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_multiple_commands(t_global *mini)
{
	t_proc			*childs;
	t_simple_cmds	*cmd;
	int				i;
	int				j;
	int				parsersize;
	int				infd;
	int				outfd;
	t_lexer			*red;
	t_lexer			*save;
	int				flag;

	i = 0;
	j = 0;
	outfd = dup(STDIN_FILENO);
	infd = dup(STDOUT_FILENO);
	cmd = mini->p_head;
	parsersize = ft_parsersize(cmd);
	// child processler, pidleri, ve pipeları bir arrayin içinde.
	childs = (t_proc *)malloc(sizeof(t_proc) * (parsersize));
	//bütün pipelar bu fonksiyonda açılıyor teker teker. pidleri 1 e eşitliyorum ki sonra 0 olanların hangi process olduğunu anlayabileyim
	while (i < parsersize)
	{
		if (pipe(childs[i].fd) == -1)
			write(2, "Pipe couldn't be opened.\n", 26);
		childs[i].pid = 1;
		i++;
	}
	// burada parent processten pipe sayısının bir fazlası kadar(parserdaki node sayısı eder aynı zamanda) process açılıyor. bütün processlerin parser listesinin başını yani şu anda olduğu node u processin sıra numarasına eşit node una eşitliyorum. örneğin parser cat->ls şeklindeyse ilk processin parser->str[0] ı cat ikincisnin ls oluyor
	// ft_set_path envdeki pathlerin içerisinde komutun olup olmadığına bakıyor mesela bin/cat adlı bir dosya varsa cmd->str[0] ı bin/cat yapıyor. execveyi ancak bin/cat şeklinde çalıştırabiliyoruz.
	i = 0;
	while (i < parsersize)
	{
		if (ft_isparent(childs, parsersize))
			childs[i].pid = fork();
		if (childs[i].pid == 0)
		{
			cmd = ft_find_parser_index(i, mini->p_head);
			cmd->str[0] = ft_set_path(mini, &(cmd->str[0]));
			close(outfd);
			infd = childs[i].fd[0];
			if (i < parsersize - 1 && !flag)
			{
				close(outfd);
				outfd = childs[i + 1].fd[1];
			}
			break ;
		}
		i++;
	}
	// her processin bir pipe ı var ancak array olduğu için diğer processlerin pipelarını da inherit alıyor. processin 0 pipe ı  ve sonraki processin 1 pipe ı hariç hiçbiri önemli değil hepsini kapatıyoruum zaten sonra
	// her process inputlarını o processin 0 pipeından alıyor ve outputunu sonraki processin 1 pipeına veriyor. < ve << durumlarına kendi 0 pipeına kendi 1 pipe ını kullanarak önce yazıyor, sonra execveden önce inputunu 0 a eşitleyip okuyor. yazdıktan sonra 1 i tabii ki kapatıyorum.
	// burda < << > >> durumlarında input ve outoutları değiştiriyorum. < ve << de 0 pipeına yazıp bırakıyorum. > >> de outputunu direkt olarak değiştiriyorum başka bi dosya yapıyorum. flag outputu başka bir dosya mı onu gösteriyor. bir processin outputu başka bi dosya değilse ya sonraki processtir ya da son processe standard outputtur.
	i = 0;
	while (i < parsersize)
	{
		if (childs[i].pid == 0)
		{
			flag = 0;
			red = cmd->redirections;
			while (red && red->next)
				red = red->next;
			save = red;
			ft_setinput(&red, &childs[i], &flag);
			red = save;
			flag = 0;
			ft_setoutput(&red, mini, &flag, &outfd);
		}
		i++;
	}
	// bu kısımda her processin infd sini kendi 0 pipeı outfdsini ise sonraki processin 1 pipe ı yapıyorum
	i = 0;
	while (i < parsersize)
	{
		if (childs[i].pid == 0)
		{
			close(infd);
			infd = childs[i].fd[0];
			if (i < parsersize - 1 && !flag)
			{
				close(outfd);
				outfd = childs[i + 1].fd[1];
			}
		}
		i++;
	}
	//parent dahil bütün processler output ve input dosyaları hariç BÜTÜN pipeları kapatıyor. execve output ve inputu kendi kapatacağı için onları kapatmaya gerek yok ki kapatırsak hata verir.
	i = 0;
	while (i < parsersize)
	{
		if (outfd != childs[i].fd[1])
			close(childs[i].fd[1]);
		if (infd != childs[i].fd[0])
			close(childs[i].fd[0]);
		i++;
	}
	// komutların inputunu infdye outputunu outfd ye kopyalıyorum.kopyalandığı için gereksiz olan infd ve outfd yi kapatıp komutları çalıştırıyorum. fark ettiysen child.pid == 0 kontrolü yapmıyorum çünkü hepsi aynı anda çalışsın istiyorum.
	i = 0;
	if (!ft_isparent(childs,parsersize))
	{
		dup2(infd,STDIN_FILENO);
		dup2(outfd,(STDOUT_FILENO));
		close(infd);
		close(outfd);
		execve(cmd->str[0], cmd->str, mini->env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	// parent bütün processleri bekliyor ki hepsi bitene kadar hiçbirşey yapmasın.
	if (ft_isparent(childs, parsersize))
	{
		while (i < parsersize)
		{
			waitpid(childs[i].pid, NULL, 0);
			i++;
		}
		i = 0;
	}
	close(infd);
	close(outfd);
	free(childs);
	return (0);
}
// bu fonksiyon sadece parent processte 1 döndğrğyor. eğer childdaysan 0 döndürüyor.

int	ft_isparent(t_proc *childs, int parsersize)
{
	int	i;

	i = 0;
	while (i < parsersize)
	{
		if (childs[i].pid == 0)
			return (0);
		i++;
	}
	return (1);
}

t_simple_cmds	*ft_find_parser_index(int i, t_simple_cmds *parser)
{
	int	j;

	j = 0;
	while (j < i)
	{
		parser = parser->next;
		j++;
	}
	return (parser);
}
