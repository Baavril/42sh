#!/usr/bin/env perl
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    moulinette42sh.pl                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/17 12:39:54 by abarthel          #+#    #+#              #
#    Updated: 2019/09/17 13:19:40 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

use warnings;
use strict;
use 5.010;
use Term::ANSIColor;

sub test_shell{

	my $shell = $_[0];
	my $refname_shell = $_[1];

	foreach my $arg (@ARGV)
	{
		# Put content of test in variable for substitution	
		my $content;
		open(my $fh, '<', $arg) or die "cannot open file $arg";
		{
			local $/;
			$content = <$fh>;
		}
		close($fh);

		# Replace with the name of the tested shell in file content
		$content =~ s/\.\/minishell/$shell/g;
		
		# Put content into a file for shell test
		my $filename = "input.test.tmp";
		open(FH, '>', $filename) or die $!;
		print FH $content;
		close(FH);
		
		# Test the shell
		my $output =  `$shell < $filename 2>&1`;
		$output =~ s/$refname_shell//g;

		system("rm $filename");

		return $output;
	}
}

sub logError{

	my $filename1 = "error_a.log";
	open(FH, '>', $filename1) or die $!;
	print FH $_[0];
	close(FH);
	
	my $filename2 = "error_b.log";
	open(FH, '>', $filename2) or die $!;
	print FH $_[1];
	close(FH);
	
	# Comment these two lines to avoid making the diff and removing output files
	system("diff ${filename1} ${filename2} > diff_test.log");
	system("rm -f error_a.log");
	system("rm -f error_b.log");

	# Display diff for log to be caputre in Travis.ci log
	system("cat diff_test.log");   # Comment these two lines
	system("rm -f diff_test.log"); # if you want a diff.log file
}

sub compareOutput{

	if (($_[1] ne $_[0]))
	{
		print colored( 'KO', 'red' ), "\n";
		logError($_[0], $_[1]);
		return (1);
	}
	else
	{
		print colored( 'OK', 'green' ), "\n";
		return (0);
	}
}

sub testFile{

	if (not -e './42sh') {
		print colored( '42sh does not exist, please compile it !', 'red' ), "\n";
		exit(1);
	}
}

testFile;
my $testnb = -1;
my $ret_value = 0;

my $reference_shell = 'bash --posix';
my $refname_shell = 'bash';
my $tested_shell = './42sh';
my $testname_shell = '\./42sh';

my $first_shell_output = test_shell($reference_shell, $refname_shell);
my $second_shell_output = test_shell($tested_shell, $testname_shell);

foreach my $arg (@ARGV)
{
	print colored ( "Filename:", 'blue' ), " " ,colored( $arg, 'yellow' ), ": ";
	compareOutput($first_shell_output, $second_shell_output);
	print colored ("----", 'green'), "\n";
}
exit(0);
