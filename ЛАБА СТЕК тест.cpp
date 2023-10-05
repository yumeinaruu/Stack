//Убрать нечетные элементы из стека
#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <string>

struct Stack {
    int info;
    Stack* next;
};
Stack* InStack(Stack*, int);
void View(Stack*);
void Del_All(Stack**);
void RemoveOdd(Stack**);


Stack* InStack(Stack* p, int in) {
    Stack* t = new Stack;
    t->info = in;
    t->next = p;
    return t;
}

bool check(std::string a, int type) {
    std::string num = "1234567890.-\0";;//Допустимые значения

    int MIN = 23233232;
    int min = 0;

    int DOT = 23233232;
    int dot = 0;

    int h = 0;
    bool r = 0;

    for (int i = 0; i < num.length(); i++) {
        for (int j = 0; j < a.length(); j++) {
            if (a[j] == num[i]) {
                h++;
                if (a[j] == '.') {
                    dot++;
                    DOT = j;
                }
                if (a[j] == '-') {
                    min++;
                    MIN = j;
                    if (j != 0) return 0;
                }
            }
        }
    }

    //Проверка на то, чтоб после минуса была цифра
    bool minGood = 0;
    if (MIN == 0 && min <= 1) {
        for (int i = 0; i < num.length(); i++) {
            if (a[1] == num[i]) minGood = 1;
        }
    }
    else minGood = 0;
    if (type == 1 && minGood == 1) return 0;

    //Проверка с точками
    bool dotGood1 = 0;
    bool dotGood = 0;
    if (dot == 1 && DOT != 23233232) {
        for (int i = 0; i < num.length() - 2; i++) {
            if (DOT == 0) return 0;
            else if (a[DOT - 1] == num[i]) dotGood1 = 1;
        }

        if (dotGood1) {
            for (int i = 0; i < num.length() - 2; i++) {
                if (a[DOT + 1] == num[i]) dotGood = 1;
            }
        }
    }
    if (type == 1 && dotGood == 1) return 0;
    else if (type == 2 && dotGood == 1) return 0;

    //Если всё ок, значит было введено число
    if (h == a.length()) {
        if (dotGood != 1 && DOT != 23233232) return 0;
        else if (minGood != 1 && MIN != 23233232) return 0;
        else r = 1;
    }
    else return 0;

    return r;
}

void View(Stack* p) {
    Stack* t = p;
    while (t != NULL) {
        std::cout << " " << t->info;
        t = t->next;
    }
}

void Del_All(Stack** p) {
    Stack* t = NULL;
    while (*p != NULL) {
        t = *p;
        *p = (*p)->next;
        delete t;
    }
}

void RemoveOdd(Stack** p) {
    Stack* prev = NULL;
    Stack* curr = *p;
    while (curr != NULL) {
        if (curr->info % 2 != 0) {
            if (prev != NULL) {
                prev->next = curr->next;
            }
            else {
                *p = curr->next;
            }
            Stack* temp = curr;
            curr = curr->next;
            delete temp;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void Sort_info(Stack* p) {
    Stack* t = NULL, * t1;
    int r;
    do {
        for (t1 = p; t1->next != t; t1 = t1->next)
            if (t1->info > t1->next->info) {
                r = t1->info;
                t1->info = t1->next->info;
                t1->next->info = r;
            }
        t = t1;
    } while (p->next != t);
}

void Sort_p(Stack** p, int element) {
    Stack* new_node = new Stack;
    new_node->info = element;
    new_node->next = *p;

    *p = new_node;
    Stack* t = NULL, * t1, * r;
    if ((*p)->next->next == NULL) return;
    do {
        for (t1 = *p; t1->next->next != t; t1 = t1->next)
            if (t1->next->info > t1->next->next->info) {
                r = t1->next->next;
                t1->next->next = r->next;
                r->next = t1->next;
                t1->next = r;
            }
        t = t1->next;
    } while ((*p)->next->next != t);

    Stack* to_delete = *p;
    *p = (*p)->next;
    delete to_delete;
}

void SaveToFile(Stack* p, const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) {
        printf("Error opening file %s\n", filename);
        return;
    }

    while (p != NULL) {
        fprintf_s(file, "%d\n", p->info);
        p = p->next;
    }

    fclose(file);
    printf("Stack has been saved to file %s\n", filename);
}


void ReadFromFile(Stack** p, const char* filename) {
    Stack* begin = NULL;
    Del_All(&begin);
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        printf("Error opening file %s\n", filename);
        return;
    }int value;
    while (fscanf_s(file, "%d", &value) != EOF) {
        Stack* new_elem = InStack(NULL, value);
        if (*p == NULL) {
            *p = new_elem;
        }
        else {
            Stack* current = *p;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_elem;
        }
    }

    fclose(file);
    printf("Stack has been loaded from file %s\n", filename);
}

void ViewFile(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int value;
    while (fscanf_s(file, "%d", &value) != EOF) {
        printf("%d\n", value);
    }

    fclose(file);
}

void ClearFile(const char* filename) {
    FILE* fp;
    if (fopen_s(&fp, filename, "w") == 0) {
        fclose(fp);
        printf("File %s has been cleared.\n", filename);
    }
    else {
        printf("Error opening file %s.\n", filename);
    }
}


int main() {
    setlocale(LC_CTYPE, "Russian");
    srand(time(0));
    Stack* begin = NULL, * t = NULL;
    int i, in, n = 0, kod, vvod;
    std::string skod, svvod, sn, sinn;
    bool kek = true;
    while (kek) {
        std::cout << "\nCreate - 1.\nAdd - 2.\nView - 3.\nRemove Odd - 4.\nDelete - 5.\nSort by info - 6. \nSort - 7.\nSave stack in file - 8\n"
            << "View file - 9\nClear file - 10\nRead from file - 11\nEXIT - Any other num\n";
        bool stop = 1;
        while (stop)
        {
            std::cin >> skod;
            if (check(skod, 2)) {
                kod = stoi(skod);
                stop = 0;
            }
            else std::cout << "This value should be only integer number. Try again:\n";
        }
        std::cout << "\n";
        switch (kod) {
        case 1: case 2: {
            if (kod == 1 && begin != NULL) {
                std::cout << "Clear Memory!" << std::endl;
                break;
            }

            bool lol = true;
            while (lol) {

                std::cout << "Random - 1\nBy yourself - 2\n";
                bool stop1 = 1;
                while (stop1) {
                    std::cin >> svvod;
                    if (check(svvod, 2)) {
                        vvod = stoi(svvod);
                        stop1 = 0;
                    }
                    else std::cout << "This value should be only integer number. Try again:\n";
                }

                switch (vvod) {

                case 1: {
                    std::cout << "Input quantity= ";
                    bool stop2 = 1;
                    while (stop2)
                    {
                        std::cin >> sn;
                        if (check(sn, 2)) {
                            n = stoi(sn);
                            stop2 = 0;
                        }
                        else std::cout << "This value should be only integer number. Try again:\n";
                    }
                    for (i = 1; i <= n; i++) {
                        in = rand() % 20 - 10;
                        begin = InStack(begin, in);
                    }
                    lol = false;
                    break;
                }

                case 2: {
                    std::cout << "Input quantity= ";
                    bool stop2 = 1;
                    while (stop2)
                    {
                        std::cin >> sn;
                        if (check(sn, 2)) {
                            n = stoi(sn);
                            stop2 = 0;
                        }
                        else std::cout << "This value should be only integer number. Try again:\n";
                    }
                    for (i = 1; i <= n; i++) {
                        std::cout << "Enter numbers\n";
                        bool stop3 = 1;
                        while (stop3)
                        {
                            std::cin >> sinn;
                            if (check(sinn, 2)) {
                                in = stoi(sinn);
                                stop3 = 0;
                            }
                            else std::cout << "This value should be only integer number. Try again:\n";
                        }
                        begin = InStack(begin, in);
                    }
                    lol = false;
                    break;
                }
                default: std::cout << "\nOnly 1 or 2\n"; break;
                }
            }
            break;
        }
        case 3:
            if (!begin) {
                std::cout << "\t\tStack Empty!" << std::endl;
                break;
            }
            std::cout << "\t\t--- Stack ---" << std::endl;
            View(begin);
            std::cout << std::endl;
            break;
        case 4:
            RemoveOdd(&begin);
            std::cout << "\t\tOdd elements removed!\n" << std::endl;
            break;
        case 5:
            Del_All(&begin);
            std::cout << "\t\tMemory Freed!\n" << std::endl;
            break;
        case 6:
            if (begin != NULL)  Sort_info(begin);
            std::cout << "\t\tStack is sorted!\n" << std::endl;
            break;
        case 7:
            Sort_p(&begin, n);
            std::cout << "\t\tStack is sorted!\n";
            break;
        case 8:
            if (!begin) {
                std::cout << "Stack Empty!\n" << std::endl;
                break;
            }
            SaveToFile(begin, "stack.txt");
            break;
        case 9:
            if (!begin) {
                std::cout << "File Empty!\n" << std::endl;
                break;
            }
            ViewFile("stack.txt");
            break;
        case 10:
            ClearFile("stack.txt");
            break;
        case 11:
            ReadFromFile(&begin, "stack.txt");
            break;
        default:
            std::cout << "Thanks for using program!\n";
            kek = false;
            break;
        }

    }
    return 0;
}