// Velicu Bogdan - Grupa 164
// ~~~~~~~~~~~~~~~~~~~~~~~~~

#include <stdio.h>
#include <string.h>

enum account_type {
    personal = 0,
    business = 1,
    savings = 2
};

struct account {
    char name[50];
    int balance;
    char state[50];
    int type;
};

struct bank {
    struct account accounts[100];
    int accounts_count;
};

void list_accounts(struct bank bank) {
    for (int i = 0; i < bank.accounts_count; i++) {
        printf("%i. %s %i \n", i, bank.accounts[i].name, bank.accounts[i].balance);
    }
}

int read_accounts(struct bank *bank) {
    FILE* file;
    file = fopen("tastatura.txt", "r+");
    if (file == NULL) {
        printf("Error openinig file");
        return 0;
    }
    char str[50] = "";
    struct account a = { "", 0, "", 0 };
    int bal, type;
    char name[50], state[50];
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%s %d %s %d", name, &bal, state, &type) == 4) {
            strcpy(a.name, name);

            a.balance = bal;

            strcpy(a.state, state);

            a.type = type;

            if (bank->accounts_count >= 100) {
                perror("exceeded array buffer");
                return 0;
            }

            bank->accounts[bank->accounts_count] = a;
            bank->accounts_count++;
        }
        else {
            perror("sscanf did not read 4 variables");
            return 0;
        }
    }
    fclose(file);
    return 1;
}

void write_accounts(struct bank *bank) {
    FILE* f;
    f = fopen("tastatura.txt", "w+");
    for (int i = 0; i < bank->accounts_count; i++) {
        fprintf(f, "%s %i %s %i\n", bank->accounts[i].name, bank->accounts[i].balance, bank->accounts[i].state, bank->accounts[i].type);
    }
    fclose(f);
}

void add_account(struct bank *bank) {
    struct account a = { "", 0, "", 0 };
    printf("Input: (name) (balance) (state) (type[0-2])\n");
    if (scanf("%49s %i %49s %i", a.name, &a.balance, a.state, &a.type) != 4) {
        perror("scanf did not read 4 variables");
        return;
    }
    if (bank->accounts_count >= 100) {
        perror("exceeded array buffer");
        return;
    }
    bank->accounts[bank->accounts_count] = a;
    bank->accounts_count++;
}

void delete_account(struct bank *bank) {
    int choice = -1;
    printf("Choose an account: \n");
    list_accounts(*bank);
    if (scanf("%i", &choice) != 1) {
        perror("scanf did not read 1 variable");
        return;
    }
    for (int i = choice; i < bank->accounts_count; i++) {
        bank->accounts[i] = bank->accounts[i + 1];
    }
    struct account acc = { "", 0, "", 0 };
    if (bank->accounts_count - 1 >= 100) {
        perror("exceeded array buffer");
        return;
    }
    bank->accounts[bank->accounts_count - 1] = acc; // Since we shifted all accounts
    // to the left by 1 we clear the last one from the array and substract 1 from count
    bank->accounts_count--;
}

void update_account(struct bank *bank) {
    int choice = -1;
    printf("Choose an account: \n");
    list_accounts(*bank);
    if (scanf("%i", &choice) != 1) {
        perror("scanf did not read 1 variable");
        return;
    }

    struct account a = { "", 0, "", 0 };
    printf("Input: (name) (balance) (state) (type[0-2])\n");
    if (scanf("%49s %i %49s %i", a.name, &a.balance, a.state, &a.type) != 4) {
        perror("scanf did not read 4 variables");
        return;
    }
    if (bank->accounts_count <= choice) {
        perror("chosen index is out of bounds");
        return;
    }
    if (choice >= 100) {
        perror("exceeded array buffer");
        return;
    }
    bank->accounts[choice] = a;
}

void read_account(struct bank *bank) {
    int choice = -1;
    printf("Choose an account: \n");
    list_accounts(*bank);
    if (scanf("%i", &choice) != 1) {
        perror("scanf did not read 1 variable");
        return;
    }
    if (choice >= 100) {
        perror("exceeded array buffer");
        return;
    }
    struct account a = bank->accounts[choice];
    printf("%s %i %s %i", a.name, a.balance, a.state, a.type);
}

int main() {
    struct bank bank;
    bank.accounts_count = 0;
    if (!read_accounts(&bank)) {
        return 0;
    }
    // Read files and load in memory
    while (1)
    {
        int choice = 0;

        printf("Choose action: \n");
        printf("1. Add account \n");
        printf("2. Delete account \n");
        printf("3. Update account \n");
        printf("4. Read account \n");
        printf("5. List accounts \n");
        printf("6. Exit \n");

        if (scanf("%i", &choice) != 1) {
            perror("scanf did not read 1 variable");
        }
        switch (choice) {
        case 1:
            add_account(&bank);
            break;
        case 2:
            delete_account(&bank);
            break;
        case 3:
            update_account(&bank);
            break;
        case 4:
            read_account(&bank);
            break;
        case 5:
            list_accounts(bank);
            break;
        case 6:
            write_accounts(&bank);
            // Save accounts to file on exit
            return 0;
        }
    }

    write_accounts(&bank);
    return 0;
}
