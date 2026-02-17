#include <cctype>
#include <iostream>
#include <limits>
#include <string>

struct Package
{
    std::string name;
    unsigned int basePrice;
    unsigned int includedDevices;
    unsigned int additionalDeviceCost;
};

static unsigned int calculateExtra
(
    const unsigned int includedDevices,
    const unsigned int usedDevices,
    const unsigned int additionalCost
)
{
    if (usedDevices <= includedDevices)
    {
        return 0;
    }

    const unsigned int difference = usedDevices - includedDevices;
    return difference * additionalCost;
}

static std::string toUpper(std::string value)
{
    for (char& character : value)
    {
        character = static_cast<char>(std::toupper(character));
    }

    return value;
}

static bool isValidPackage
(
    const std::string& packageType,
    const Package& packageA,
    const Package& packageB,
    const Package& packageC
)
{
    return packageType == packageA.name
        || packageType == packageB.name
        || packageType == packageC.name;
}

int main()
{
    const Package packageA{ "A", 9, 1, 6 };
    const Package packageB{ "B", 14, 3, 4 };
    const Package packageC{ "C", 20, 5, 2 };

    std::string packageType;
    std::string confirmation;
    unsigned int numberOfDevicesUsed = 0;
    bool isAllInputCorrect = false;

    std::cout << "Dear subscriber" << std::endl;

    do
    {
        do
        {
            std::cout << "Please enter the package type you are subscribed to (A, B, C):" << std::endl;
            std::getline(std::cin, packageType);
            packageType = toUpper(packageType);
        } while (!isValidPackage(packageType, packageA, packageB, packageC));

        std::cout << "Please enter the number of devices used simultaneously:" << std::endl;

        while (!(std::cin >> numberOfDevicesUsed))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid number. Please enter a valid unsigned integer:" << std::endl;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "The entered information is:" << std::endl;
        std::cout << "Subscription package: " << packageType << std::endl;
        std::cout << "Number of devices: " << numberOfDevicesUsed << std::endl;

        std::cout << "Is this correct? (Y/N):" << std::endl;
        std::getline(std::cin, confirmation);
        confirmation = toUpper(confirmation);

        isAllInputCorrect = confirmation == "Y";
    } while (!isAllInputCorrect);

    const Package* selectedPackage = nullptr;

    if (packageType == "A")
    {
        selectedPackage = &packageA;
    }
    else if (packageType == "B")
    {
        selectedPackage = &packageB;
    }
    else
    {
        selectedPackage = &packageC;
    }

    const unsigned int totalCost =
        selectedPackage->basePrice +
        calculateExtra(
            selectedPackage->includedDevices,
            numberOfDevicesUsed,
            selectedPackage->additionalDeviceCost);

    std::cout << "The total cost of your subscription is: "
        << totalCost << std::endl;

    return 0;
}
