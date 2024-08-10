#include <bits/stdc++.h>
using namespace std;

class Bank {
public:
    string name;
    int netAmount;
    set<string> types;
};

int getMinIndex(vector<Bank>& banks) {
    int minAmount = INT_MAX, minIndex = -1;
    for (int i = 0; i < banks.size(); i++) {
        if (banks[i].netAmount < minAmount) {
            minAmount = banks[i].netAmount;
            minIndex = i;
        }
    }
    return minIndex;
}

int getMaxIndex(vector<Bank>& banks, int minIndex) {
    int maxAmount = INT_MIN, maxIndex = -1;
    for (int i = 0; i < banks.size(); i++) {
        if (i != minIndex && banks[i].netAmount > maxAmount) {
            maxAmount = banks[i].netAmount;
            maxIndex = i;
        }
    }
    return maxIndex;
}

void minimizeCashFlow(vector<Bank>& banks) {
    int numZeroNetAmounts = 0;

    while (numZeroNetAmounts < banks.size()) {
        int minIndex = getMinIndex(banks);
        int maxIndex = getMaxIndex(banks, minIndex);

        if (maxIndex == -1) {
            break; // No more valid transactions possible
        }

        int transactionAmount = min(abs(banks[minIndex].netAmount), banks[maxIndex].netAmount);

        cout << banks[minIndex].name << " pays Rs " << transactionAmount << " to " << banks[maxIndex].name << endl;

        banks[minIndex].netAmount += transactionAmount;
        banks[maxIndex].netAmount -= transactionAmount;

        if (banks[minIndex].netAmount == 0) numZeroNetAmounts++;
        if (banks[maxIndex].netAmount == 0) numZeroNetAmounts++;
    }
}

int main() {
    cout << "\nWelcome to CASH FLOW MINIMIZER SYSTEM\n";
    cout << "This system minimizes the number of transactions among multiple banks using different payment modes.\n\n";
    
    cout << "Enter the number of banks: ";
    int numBanks; cin >> numBanks;

    vector<Bank> banks(numBanks);
    unordered_map<string, int> bankIndex;

    cout << "Enter the details of the banks (name, number of payment modes, and payment modes):\n";
    for (int i = 0; i < numBanks; i++) {
        cout << "Bank " << i + 1 << " (name number_of_modes mode1 mode2 ...): ";
        cin >> banks[i].name;
        bankIndex[banks[i].name] = i;

        int numModes;
        cin >> numModes;
        while (numModes--) {
            string mode;
            cin >> mode;
            banks[i].types.insert(mode);
        }
    }

    cout << "Enter the number of transactions: ";
    int numTransactions; cin >> numTransactions;

    vector<vector<int>> transactions(numBanks, vector<int>(numBanks, 0));
    cout << "Enter the transactions (debtor creditor amount):\n";
    for (int i = 0; i < numTransactions; i++) {
        string debtor, creditor;
        int amount;
        cin >> debtor >> creditor >> amount;
        transactions[bankIndex[debtor]][bankIndex[creditor]] += amount;
    }

    // Calculate net amounts
    for (int i = 0; i < numBanks; i++) {
        int netAmount = 0;
        for (int j = 0; j < numBanks; j++) {
            netAmount += transactions[j][i] - transactions[i][j];
        }
        banks[i].netAmount = netAmount;
    }

    minimizeCashFlow(banks);

    return 0;
}
