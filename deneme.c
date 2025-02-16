#include <stdio.h>
#include <unistd.h>

void
	my_putchar(char c)
{
	write(1, &c, 1);
}

// str sonu seq açık -> girdi iste
// str sonu seq kapalı -> yazdır
// boşluk seq açık -> devam et
// boşluk seq kapalı -> yazdır

int	word_counter(char *input)
{
	int	count;
	int	i;
	int	seq;

	count = 0;
	i = 0;
	seq = 0;
}

int	lexer(char *input)
{
	int	i;
	int	j;
	int	sequence;

	i = 0;
	j = 0;
	sequence = 0;
	while (input[i + j])
	{
		if (input[i + j] == '\"' || input[i + j] == '\'')
		{
			sequence = !sequence;
		}
		if ((input[i + j] == ' ' || !input[i + j + 1]) && sequence == 0)
		{
			if (!input[i + j + 1])
				j++;
			write(1, input + i, j);
			my_putchar('\n');
			i += j + 1;
			j = 0;
			continue ;
		}
		j++;
	}
	return (1);
}
int main()
{
    lexer("hello \"oguz harun bastug\"    world yusuf'oguz hello world''harun bastug'");
    return 0;
}