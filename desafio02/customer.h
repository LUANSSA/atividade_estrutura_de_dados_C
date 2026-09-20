typedef struct Customer_ Customer;

Customer* create_customer(char* name, char* district, int n_people, int children, double income);
char* get_name(Customer* customer);
char* get_district(Customer* customer);
int get_n_people(Customer* customer);
int get_children(Customer* customer);
double get_income(Customer* customer);