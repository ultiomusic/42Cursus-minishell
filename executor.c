/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baer <baer@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:55:24 by baer              #+#    #+#             */
/*   Updated: 2023/12/25 15:37:38 by baer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printmatrix(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != NULL)
	{
		while (str[i][j] != '\0')
			write(1, str[i] + j++, 1);
		write(1, " ", 1);
		j = 0;
		i++;
	}
	write(1, "\n", 1);
}

void	ft_executer(t_global *mini)
{
	if (ft_parsersize(mini->p_head) == 1)
		ft_execute_single_commands(mini);
	else if(ft_parsersize(mini->p_head) >= 1)
		ft_execute_multiple_commands(mini);
}
/*YAPILMASI GEREKENLER
	builtin fonksiyonları çalıştırmamız lazım. şu anda binden bulup çalıştırınca yanlış çalışıyor çünkü process kendi directorysini değiştiriyor, envi farklı oluyor vs. farklı insanlarınkinden de bakabilirsin bu kısma execve çalıştırmak yerine parserin builtin function pointerını çalıştırman gerekiyor. parser structunun içinde zaten bir function pointer var. kullanarak çalıştırabilirsin direkt.
	signal handling yapmıyoruz. ctrl c ctrl d gibi sinyalleri subjectte yazdığı gibi çalıştırmamız lazım. bir global variable ımı< ve bir signal handling fonksiyonumuz olacak. global variable sürekli içinde programın durumunu tutacak ki heredoc içindeyken ctrl-c ye bastığımı<da verdiği hata kodu ile normalde bastığımızda verdiği aynı olmasın.
	mini structunun içinde bir exit değişkeni oluşturup execveden gelen her exiti ve hatayı onun içinde sürekli tutmamız lazım. $? yazıldığında bu değerin ekranda belirmesi gerekiyor
	cat|cat|ls i sormamız lazım
	bu kadar.
*/