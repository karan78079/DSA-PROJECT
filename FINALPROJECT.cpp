#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>  
#include <iomanip>   
using namespace std;


class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        left = right = nullptr;
    }
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() {
        root = nullptr;
    }

    TreeNode* insert(TreeNode* node, int value) {
        if (node == NULL) {
            cout << "INSERTING NODE: " << value << endl;
            Sleep(800);
            return new TreeNode(value);
        }

        if (value < node->data) {
            cout << "GOING LEFT FROM: " << node->data << endl;
            Sleep(400);
            node->left = insert(node->left, value);
        } else {
            cout << "GOING RIGHT FROM: " << node->data << endl;
            Sleep(400);
            node->right = insert(node->right, value);
        }

        return node;
    }

    void insertValue(int value) {
        root = insert(root, value);
    }

    void visualize(TreeNode* node, int space = 0, int height = 10) {
        if (!node) return;

        space += height;
        visualize(node->right, space);

        cout << endl;
        for (int i = height; i < space; i++)
            cout << " ";
        cout << " " << node->data << "\n";

        visualize(node->left, space);
    }
    
    
    

    void preorder(TreeNode* node) {
        if (node==NULL) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
    
    
    

    void inorder(TreeNode* node) {
        if (node==NULL) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    
    

    void postorder(TreeNode* node) {
        if (node==NULL) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }
    
    
    

    void levelOrder(TreeNode* node) {
        if (node==NULL) return;

        queue<TreeNode*> q;
        q.push(node);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            cout << current->data << " ";

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }
    
    
    
    

    void startVisualization() {
        cout << "\nFinal Tree Visualization:\n\n";
        Sleep(1000);
        visualize(root);
    }
    
    
    

    void performTraversal() {
        int choice;
        cout << "\nChoose traversal \n";
        cout << "1. Preorder\n";
        cout << "2. Inorder\n";
        cout << "3. Postorder\n";
        cout << "4. Level Order\n";
        cout << "Enter choice: ";
        cin >> choice;

        cout << "\nTraversal Output:\n";
        switch (choice) {
        case 1:
            preorder(root);
            break;
        case 2:
            inorder(root);
            break;
        case 3:
            postorder(root);
            break;
        case 4:
            levelOrder(root);
            break;
        default:
            cout << "Invalid choice.";
        }
        cout << endl;
    }
};

void runBinaryTree() {
    BinaryTree bt;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    cout << "\nInserting values into BST...\n";
    for (int i = 0; i < n; i++) {
        bt.insertValue(values[i]);
        Sleep(500);
    }

    bt.startVisualization();
    bt.performTraversal();
}


class Employee {
public:
    string name;
    vector<Employee*> subordinates;

    Employee(string name) {
        this->name = name;
    }

    void addSubordinate(Employee* emp) {
        subordinates.push_back(emp);
    }
};

void printTree(Employee* root, string indent = "", bool last = true) {
    cout << indent;
    if (last) {
        cout << "+-- ";
        indent += "    ";
    } else {
        cout << "|-- ";
        indent += "|   ";
    }
    cout << root->name << endl;

    for (size_t i = 0; i < root->subordinates.size(); ++i) {
        printTree(root->subordinates[i], indent, i == root->subordinates.size() - 1);
    }
}

void printLevelOrder(Employee* root) {
    if (!root) return;

    queue<Employee*> q;
    q.push(root);

    cout << "\nLevel Order Traversal (Top to Bottom):\n";
    while (!q.empty()) {
        Employee* current = q.front();
        q.pop();
        cout << current->name << " ";

        for (Employee* sub : current->subordinates) {
            q.push(sub);
        }
    }
    cout << endl;
}

Employee* findEmployee(const string& name, const vector<Employee*>& employees) {
    for (Employee* e : employees) {
        if (e->name == name) return e;
    }
    return nullptr;
}

void runOrgTree() {
    vector<Employee*> employees;
    string name;

    cout << "Enter CEO name (root of tree): ";
    getline(cin, name);
    Employee* ceo = new Employee(name);
    employees.push_back(ceo);

    int choice;
    do {
        cout << "\n--- Organizational Tree Menu ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Tree Structure\n";
        cout << "3. Level Order Traversal\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string managerName, employeeName;
            cout << "Enter manager's name: ";
            getline(cin, managerName);
            cout << "Enter employee's name: ";
            getline(cin, employeeName);

            Employee* manager = findEmployee(managerName, employees);
            if (manager) {
                Employee* newEmp = new Employee(employeeName);
                manager->addSubordinate(newEmp);
                employees.push_back(newEmp);
                cout << "Employee added under " << managerName << ".\n";
            } else {
                cout << "Manager not found.\n";
            }
            break;
        }
        case 2:
            cout << "\nOrganizational Tree:\n";
            printTree(ceo);
            break;
        case 3:
            printLevelOrder(ceo);
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    for (Employee* e : employees)
        delete e;
}


int main() {
    int mainChoice;

    do {
        cout << "\n===== OPTIONS: =====\n";
        cout << "1. Binary Search Tree Visualization\n";
        cout << "2. Organizational Hierarchy Tree\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;
        cin.ignore();

        switch (mainChoice) {
        case 1:
            runBinaryTree();
            break;
        case 2:
            runOrgTree();
            break;
        case 3:
            cout << "Exiting... Thank you!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (mainChoice != 3);

    return 0;
}
