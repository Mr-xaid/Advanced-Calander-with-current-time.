#include <stdio.h>
#include <time.h>

int main() {
    int current_year, current_month;
    time_t current_time;
    struct tm *current_tm;

    // Get the current time
    time(&current_time);
    current_tm = localtime(&current_time);
    current_year = current_tm->tm_year + 1900; // Years since 1900
    current_month = current_tm->tm_mon;        // Month (0 - 11, January is 0)

    // Ask the user for the year and month
    int target_year, target_month;
    printf("Enter the year (e.g., 2023): ");
    if (scanf("%d", &target_year) != 1 || target_year < 0) {
        printf("Invalid year. Please enter a valid year.\n");
        return 1; // Exit with an error code
    }

    printf("Enter the month (1-12): ");
    if (scanf("%d", &target_month) != 1 || target_month < 1 || target_month > 12) {
        printf("Invalid month. Please enter a valid month.\n");
        return 1; // Exit with an error code
    }

    // Calculate the number of days in the target month
    int days_in_month;
    if (target_month == 12) {
        days_in_month = 31; // December
    } else {
        days_in_month = (int[]){31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}[target_month - 1];
    }

    // Display the calendar for the specified month and year
    printf("\nCalendar for %d/%d:\n", target_month, target_year);
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    struct tm date_tm = {0};
    date_tm.tm_year = target_year - 1900;
    date_tm.tm_mon = target_month - 1;
    date_tm.tm_mday = 1;
    mktime(&date_tm);

    // Print leading spaces for the first day of the month
    for (int i = 0; i < date_tm.tm_wday; i++) {
        printf("    ");
    }

    // Print the days of the month
    for (int day = 1; day <= days_in_month; day++) {
        printf("%3d ", day);
        if ((date_tm.tm_wday + day) % 7 == 6) {
            printf("\n");
        }
    }

    // Ask the user if they want to calculate the difference between two dates
    char choice;
    printf("\nDo you want to calculate the difference between two dates (Y/N)? ");
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y') {
        // Calculate the difference between two dates
        struct tm date1, date2;
        char date_str[20];
        printf("Enter the first date (day/month/year): ");
        if (scanf("%d/%d/%d", &date1.tm_mday, &date1.tm_mon, &date1.tm_year) != 3 || date1.tm_mday < 1 || date1.tm_mday > days_in_month || date1.tm_mon < 1 || date1.tm_mon > 12) {
            printf("Invalid date format or date out of range. Please enter a valid date.\n");
            return 1; // Exit with an error code
        }
        date1.tm_year -= 1900; // Adjust year as needed

        printf("Enter the second date (day/month/year): ");
        if (scanf("%d/%d/%d", &date2.tm_mday, &date2.tm_mon, &date2.tm_year) != 3 || date2.tm_mday < 1 || date2.tm_mday > days_in_month || date2.tm_mon < 1 || date2.tm_mon > 12) {
            printf("Invalid date format or date out of range. Please enter a valid date.\n");
            return 1; // Exit with an error code
        }
        date2.tm_year -= 1900; // Adjust year as needed

        // Calculate the difference between two dates based on the date part only
        int days_difference = date2.tm_mday - date1.tm_mday;
        int months_difference = date2.tm_mon - date1.tm_mon;
        int years_difference = date2.tm_year - date1.tm_year;

        // Normalize the difference by considering negative values
        if (days_difference < 0) {
            months_difference--;
            days_difference += days_in_month;
        }
        if (months_difference < 0) {
            years_difference--;
            months_difference += 12;
        }

        // Display the difference
        printf("Difference between the selected dates: %d days, %d months, %d years\n", days_difference, months_difference, years_difference);
    }

    // Ask the user if they want to see the current time
    printf("Do you want to see the current time (Y/N)? ");
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y') {
        // Get and display the current time
        time(&current_time);
        current_tm = localtime(&current_time);
        printf("Current Time: %02d:%02d:%02d\n", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec);
    }

    return 0;
}
