// EGN3211 Project 2 - Mortgage Calculator in C
// Taniya Shaffer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

#define FILE1 "output1.txt"
#define FILE2 "output2.txt"
#define FILE3 "output3.txt"
#define FILE4 "output4.txt"
#define MONTHS 12

#define LOAN 280000
#define INTEREST 3.00
#define YEARS 30
#define MONTHLY_EXTRA 500
#define ANNUAL_EXTRA 4000


void output_short_format(double loan_amount, double interest_rate, double term_years);
void output_amortized(double loan_amount, double interest_rate, double term_years);
void output_extra_monthly(double loan_amount, double interest_rate, double term_years, double extra);
void output_extra_yearly(double loan_amount, double interest_rate, double term_years, double extra);
void menu(int value);

int main()
{
	int choice, i, value;

	while (choice != -1)
	{
		menu(1);
	}

	return 0;
}

// Calculates and prints the monthly payment, total interest, and total amount paid based on the loan amount, interest rate, and term.
void output_short_format(double loan_amount, double interest_rate, double term_years)
{
	FILE * fPtr;

	// Checking if file pointer exists
	if( (fPtr = fopen(FILE1, "w")) == NULL)
	{
        printf("File could not be opened!... Exiting program.\n");
        return;
    }

	int i, months = (term_years * MONTHS);
	double m_payment, m_rate = ((interest_rate/100) / MONTHS), exp = pow((1 + m_rate), months);
	double total_paid, total_interest;

	// Formatting header
	{
		for (i = 0; i <= 33; i++)
		{
			if (DEBUG) printf("-"); else fprintf(fPtr, "-");
		}
		if (DEBUG) printf("\n\t   LOAN TERMS\n"); else fprintf(fPtr, "\n\t\t\tLOAN TERMS\n");
		for (i = 0; i <= 33; i++)
		{
			if (DEBUG) printf("-"); else fprintf(fPtr, "-");
		}
	}

	if (DEBUG) printf("\nLoan Amount: %15.0f\n", loan_amount); else fprintf(fPtr, "\nLoan Amount: %15.0f\n", loan_amount);
	if (DEBUG) printf("Interest Rate: %12.2f%%\n", interest_rate); else fprintf(fPtr, "Interest Rate: %12.2f%%\n", interest_rate);
	if (DEBUG) printf("Term: %16.0f years\n", term_years); else fprintf(fPtr, "Term: %16.0f years\n", term_years);
	
	for (i = 0; i <= 33; i++)
	{
		if (DEBUG) printf("-"); else fprintf(fPtr, "-");
	}

	//m_payment = loan_amount * m_rate * (1 + m_rate)^months / [((1 + m_rate)^months) - 1]
	m_payment = loan_amount * m_rate * exp / (exp - 1);

	total_paid = m_payment * months;

	total_interest = total_paid - loan_amount;

	// Printing time
	if (DEBUG) printf("\n"); else fprintf(fPtr, "\n");
	if (DEBUG) printf("Monthly payment is: %11.2f\n", m_payment); else fprintf(fPtr, "Monthly payment is: %11.2f\n", m_payment);
	if (DEBUG) printf("Total interest is: %12.2f\n", total_interest); else fprintf(fPtr, "Total interest is: %12.2f\n", total_interest);
	if (DEBUG) printf("Total amount paid is: %.2f\n", total_paid); else fprintf(fPtr, "Total amount paid is: %.2f\n", total_paid);

	fclose(fPtr);
}

// Shows the amounts that go towards interest and principal for each month.
void output_amortized(double loan_amount, double interest_rate, double term_years)
{
	FILE * fPtr;

	// Checking if file pointer exists
	if( !DEBUG && (fPtr = fopen(FILE2, "w")) == NULL)
	{
        printf("File could not be opened!... Exiting program.\n");
        return;
    }

	int i, months = (term_years * MONTHS), year, current_month;
	double m_payment, m_rate = ((interest_rate/100) / MONTHS), exp = pow((1 + m_rate), months);
	double principal_paid = 0, interest_paid = 0;
	double initial_loan_amount = loan_amount;

	//m_payment = loan_amount * m_rate * (1 + m_rate)^months / [((1 + m_rate)^months) - 1]
	m_payment = loan_amount * m_rate * exp / (exp - 1);



	year = 1;
	current_month = 1;

	// While you still got a debt to pay
	while (loan_amount >= 0.01)
	{
		if (DEBUG) printf("\n"); else fprintf(fPtr, "\n");

		// Loop through 12 months
		for (i = 0; i <= 64; i++)
		{
			if (DEBUG) printf("-"); else fprintf(fPtr, "-");
		}
	
		if (DEBUG) printf("\nYear  Month  Interest  Principal  Balance  |  INTEREST  PRINCIPAL\n");
		else fprintf(fPtr, "\nYear  Month  Interest  Principal  Balance  |  INTEREST  PRINCIPAL\n");
	
		for (i = 0; i <= 64; i++)
		{
			if (DEBUG) printf("-"); else fprintf(fPtr, "-");
		}

		if (DEBUG) printf("\n%d", year); else fprintf(fPtr, "\n%d", year);
		for (i = 1; i <= MONTHS; i++)
		{
			// Printing tabs in lieu of same year section
			if (DEBUG) printf("\t"); else fprintf(fPtr, "\t\t");
			
			// Monthly payments
			double m_interest = loan_amount * m_rate;
			double m_principal = m_payment - m_interest;
		
			// Total payments
			interest_paid += m_interest;
			principal_paid += m_principal;
			loan_amount -= m_principal;

			// Print it out all fancy
			if (DEBUG) 
				printf("%3d", current_month); 
			else 
				fprintf(fPtr, "%3d", current_month);

			if (DEBUG) 
				printf("%10.0f", m_interest); 
			else 
				fprintf(fPtr, "%10.0f", m_interest);

			if (DEBUG) 
				printf("%11.0f", m_principal); 
			else 
				fprintf(fPtr, "%11.0f", m_principal);

			if (DEBUG) 
				printf("%9.0f", loan_amount); 
			else 
				fprintf(fPtr, "%9.0f", loan_amount);

			if (DEBUG) 
				printf("  |"); 
			else 
				fprintf(fPtr, "  |");

			if (DEBUG) 
				printf("%10.0f", interest_paid); 
			else 
				fprintf(fPtr, "%10.0f", interest_paid);

			if (DEBUG) 
				printf("%11.0f", principal_paid); 
			else 
				fprintf(fPtr, "%11.0f", principal_paid);

			if (DEBUG) 
				printf("\n"); 
			else 
				fprintf(fPtr, "\n");


			// Last minute bidness
			current_month++;
		}

		year++;
	}
	if (!DEBUG) fclose(fPtr);
}

// Including optional extra towards payment every month, then prints out how much interest saving and finished paying back within x number of months.
void output_extra_monthly(double loan_amount, double interest_rate, double term_years, double extra)
{
	FILE * fPtr;

	// Checking if file pointer exists
	if( (!DEBUG) && (fPtr = fopen(FILE3, "w")) == NULL)
	{
        printf("File could not be opened!... Exiting program.\n");
        return;
    }

	int i, months = (term_years * MONTHS), year, current_month, month_diff = 0;
	double m_payment, m_rate = ((interest_rate/100) / MONTHS), exp = pow((1 + m_rate), months); 
	double principal_paid = 0, interest_paid = 0, year_diff = 0;
	double total_interest, total_paid, interest_diff = 0;


	//m_payment = loan_amount * m_rate * (1 + m_rate)^months / [((1 + m_rate)^months) - 1]
	m_payment = loan_amount * m_rate * exp / (exp - 1);
	total_paid = m_payment * months;
	total_interest = total_paid - loan_amount;

	year = 1;
	current_month = 0;

	// While you still got a debt to pay
	while (loan_amount >= 0.01)
	{
		if (DEBUG) 
			printf("\n"); 
		else 
			fprintf(fPtr, "\n");
		for (i = 0; i <= 71; i++)
		{
			if (DEBUG) 
				printf("-"); 
			else 
				fprintf(fPtr, "-");
		}
	
		if (DEBUG) 
			printf("\nYear  Month  Interest  Principal  Balance  |  INTEREST  PRINCIPAL  EXTRA\n"); 
		else 
			fprintf(fPtr, "\nYear  Month  Interest  Principal  Balance  |  INTEREST  PRINCIPAL  EXTRA\n");
	
		for (i = 0; i <= 71; 
			i++)
		{

			if (DEBUG) 
				printf("-"); 
			else 
				fprintf(fPtr, "-");
		}

		if (DEBUG) 
			printf("\n%d", year); 
		else 
			fprintf(fPtr, "\n%d", year);

		// Loop through 12 months
		for (i = 1; i <= MONTHS && (loan_amount >= 0.01); i++)
		{
			current_month++;
			if (DEBUG) 
				printf("\t"); 
			else 
				fprintf(fPtr, "\t\t");

			// Monthly payments
			double m_interest = loan_amount * m_rate;
			double m_principal = m_payment - m_interest;

			// Total payments
			interest_paid += m_interest;
			principal_paid += m_principal + extra;
			loan_amount -= m_principal + extra;

			// Print it out all fancy
			if (DEBUG) 
				printf("%3d", current_month); 
			else 
				fprintf(fPtr, "%3d", current_month);

			if (DEBUG) 
				printf("%10.0f", m_interest); 
			else 
				fprintf(fPtr, "%10.0f", m_interest);

			if (DEBUG) 
				printf("%11.0f", m_principal); 
			else 
				fprintf(fPtr, "%11.0f", m_principal);

			if (DEBUG) 
				printf("%9.0f", loan_amount); 
			else 
				fprintf(fPtr, "%9.0f", loan_amount);

			if (DEBUG) 
				printf("  |"); 
			else 
				fprintf(fPtr, "  |");

			if (DEBUG) 
				printf("%10.0f", interest_paid); 
			else 
				fprintf(fPtr, "%10.0f", interest_paid);

			if (DEBUG) 
				printf("%11.0f", principal_paid); 
			else 
				fprintf(fPtr, "%11.0f", principal_paid);

			if (DEBUG) 
				printf("%7.0f\t\t", extra); 
			else fprintf(fPtr, "%7.0f\t\t", extra);
			if (DEBUG) 
				printf("\n"); 
			else fprintf(fPtr, "\n");
		}
		year++;
	}
	
	// Printing out savings of both time and money by paying extra
	if (DEBUG) 
		printf("\n"); 
	else 
		fprintf(fPtr, "\n");

	month_diff = months - current_month;
	year_diff = term_years - ((double)current_month / (double)MONTHS);
	interest_diff = total_interest - interest_paid;
	if (DEBUG) 
		printf("\nThe payments are finished %d months (%.1f years) earlier!\n", month_diff, year_diff);  
	else 
		fprintf(fPtr, "\nThe payments are finished %d months (%.1f years) earlier!\n", month_diff, year_diff);

	if (DEBUG) 
		printf("The interest saving is %.0f", interest_diff);  
	else 
		fprintf(fPtr, "The interest saving is %.0f", interest_diff);
	
	// Closing file pointer
	if (!DEBUG) fclose(fPtr);
}

void output_extra_yearly(double loan_amount, double interest_rate, double term_years, double extra)
{
	FILE * fPtr;

	// Checking if file pointer exists
	if ( (!DEBUG) && (fPtr = fopen(FILE4, "w")) == NULL)
	{
			printf("File could not be opened!... Exiting program.\n");
        return;
    }

	int i, months = (term_years * MONTHS), year, current_month, month_diff = 0;
	double m_payment, m_rate = ((interest_rate/100) / MONTHS), exp = pow((1 + m_rate), months); 
	double principal_paid = 0, interest_paid = 0, year_diff = 0;
	double total_interest, total_paid, interest_diff = 0;

	//m_payment = loan_amount * m_rate * (1 + m_rate)^months / [((1 + m_rate)^months) - 1]
	m_payment = loan_amount * m_rate * exp / (exp - 1);
	total_paid = m_payment * months;
	total_interest = total_paid - loan_amount;

	year = 1;
	current_month = 0;

	// While you still got a debt to pay
	while (loan_amount >= 0.01)
	{
		if (DEBUG) 
			printf("\n"); 
		else 
			fprintf(fPtr, "\n");
		for (i = 0; i <= 71; i++)
		{
			if (DEBUG) 
				printf("-"); 
			else 
				fprintf(fPtr, "-");
		}
	
		if (DEBUG) 
			printf("\nYear  Month  Interest  Principal  Balance  |  INTEREST  PRINCIPAL  EXTRA\n"); 
		else 
			fprintf(fPtr, "\nYear  Month  Interest  Principal  Balance  |  INTEREST  PRINCIPAL  EXTRA\n");
	
		for (i = 0; i <= 71; i++)
		{

			if (DEBUG) 
				printf("-"); 
			else 
				fprintf(fPtr, "-");
		}
	
		if (DEBUG) 
			printf("\n%d", year); 
		else 
			fprintf(fPtr, "\n%d", year);

		// Loops through 12 months
		for (i = 1; i <= MONTHS && (loan_amount >= 0.01); i++)
		{
			current_month++;
			if (DEBUG) 
				printf("\t"); 
			else 
				fprintf(fPtr, "\t\t");

			// Monthly payments
			double m_interest = loan_amount * m_rate;
			double m_principal = m_payment - m_interest;

			// Total payments
			interest_paid += m_interest;
			principal_paid += m_principal;
			loan_amount -= m_principal;

			// Print it out all fancy
			if (DEBUG) 
				printf("%3d", current_month); 
			else 
				fprintf(fPtr, "%3d", current_month);

			if (DEBUG) 
				printf("%10.0f", m_interest); 
			else 
				fprintf(fPtr, "%10.0f", m_interest);

			if (DEBUG) 
				printf("%11.0f", m_principal); 
			else 
				fprintf(fPtr, "%11.0f", m_principal);

			if (DEBUG) 
				printf("%9.0f", loan_amount); 
			else 
				fprintf(fPtr, "%9.0f", loan_amount);

			if (DEBUG) 
				printf("  |"); 
			else 
				fprintf(fPtr, "  |");

			if (DEBUG) 
				printf("%10.0f", interest_paid); 
			else 
				fprintf(fPtr, "%10.0f", interest_paid);

			if (DEBUG) 
				printf("%11.0f", principal_paid); 
			else 
				fprintf(fPtr, "%11.0f", principal_paid);


	      	if (i == MONTHS)
			{
				loan_amount -= extra;
				principal_paid += extra;
				if (DEBUG) 
					printf("%7.0f\t\t", extra); 
				else fprintf(fPtr, "%7.0f\t\t", extra);
		    }
			
			if (DEBUG) 
				printf("\n"); 
			else fprintf(fPtr, "\n");
		}
		year++;
	}

	// Printing out savings of both time and money by paying extra
	if (DEBUG) 
		printf("\n"); 
	else 
		fprintf(fPtr, "\n");

	month_diff = months - current_month;
	year_diff = term_years - ((double)current_month / (double)MONTHS);
	interest_diff = total_interest - interest_paid;
	if (DEBUG) 
		printf("\nThe payments are finished %d months (%.1f years) earlier!\n", month_diff, year_diff);  
	else 
		fprintf(fPtr, "\nThe payments are finished %d months (%.1f years) earlier!\n", month_diff, year_diff);

	if (DEBUG) 
		printf("The interest saving is %.0f", interest_diff);  
	else 
		fprintf(fPtr, "The interest saving is %.0f", interest_diff);
	
	// Closing file pointer
	if (!DEBUG) fclose(fPtr);
}

// Main menu function
// NOTE: IF #define DEBUG 0, it will not print to console but .txt. file. IF #define DEBUG 1, it will print to console.
void menu(int value)
{
	int choice, i;

	if (value == 1)
	{
		printf("HELLO. I AM A MORTGAGE CALCULATOR.\n");
		for (i = 0; i <= 33; i++)
		{
			printf("-");
		}
		printf("\n");
		printf("PLEASE SELECT AN OPTION BELOW. TYPE IN THE NUMBER OF THE MENU YOU WOULD LIKE TO ACCESS.\n");
		printf("1 - Output, Short Format\n");
		printf("2 - Output, Amortized Schedule\n");
		printf("3 - Output, Monthly Extra Schedule\n");
		printf("4 - Output, Yearly Extra Schedule\n");
		printf("\nOR TYPE IN -1 IF YOU ARE DONE.\n");
		scanf("%d", &choice);
		switch (choice)
		{
			case 1: system("cls");
					output_short_format(LOAN,INTEREST,YEARS);
					printf("\n\nWOULD YOU LIKE TO GO BACK TO THE MAIN MENU? (1 = YES / 2 = NO)\n\n");
					scanf("%d", &value);
					if (value == 1)
					{
						system("cls");
						menu(1);
					}
					else
						exit(0);
					break;
			case 2: system("cls");
					output_amortized(LOAN,INTEREST,YEARS);
					printf("\n\nWOULD YOU LIKE TO GO BACK TO THE MAIN MENU? (1 = YES / 2 = NO)\n\n");
					scanf("%d", &value);
					if (value == 1)
					{
						system("cls");
						menu(1);
					}
					else
						exit(0);
					break;
			case 3: system("cls");
					output_extra_monthly(LOAN,INTEREST,YEARS, MONTHLY_EXTRA);
					printf("\n\nWOULD YOU LIKE TO GO BACK TO THE MAIN MENU? (1 = YES / 2 = NO)\n\n");
					scanf("%d", &value);
					if (value == 1)
					{
						system("cls");
						menu(1);
					}
					else
						exit(0);
					break;
			case 4: system("cls");
					output_extra_yearly(LOAN,INTEREST,YEARS, ANNUAL_EXTRA);
					printf("\n\nWOULD YOU LIKE TO GO BACK TO THE MAIN MENU? (1 = YES / 2 = NO)\n\n");
					scanf("%d", &value);
					if (value == 1)
					{
						system("cls");
						menu(1);
					}
					else
						exit(0);
					break;
			case -1: exit(0);
			default: printf("PLEASE TRY AGAIN. ENTER VALUES 1-4 TO SELECT AN OPTION.");
					break;
		}
	}
	else
		exit(0);
}
