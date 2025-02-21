#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "hospital_records.txt"

typedef struct 
{
    int id;
    char name[50];
    int age;
    char gender[10];
    char contact[15];
    char address[100];
    char email[50];
    char marital_status[20];
    char nationality[30];
    char emergency_contact[15];
    char insurance_number[30];
} PersonalDetails;

typedef struct {
    char blood_type[5];
    char disease[50];
    float cost;
    char allergies[100];
    char medical_history[200];
    char medication[100];
    char previous_surgeries[200];
    char family_history[100];
    int height;
    int weight;
    char smoking_status[20];
} HealthDetails;

typedef struct 
{
    char treatment[100];
    char doctor[50];
    char treatment_date[20];
    char hospital_name[100];
    char treatment_type[50];
    char prescription[200];
    char follow_up_date[20];
    char doctor_contact[15];
    char room_number[10];
    char treatment_status[20];
    char admission_date[20];
} TreatmentDetails;

typedef struct 
{
    PersonalDetails personal;
    HealthDetails health;
    TreatmentDetails treatment;
} PatientRecord;

void mainMenu();
void registerPatient();
void viewPatients();
void searchPatientByID();
void deletePatientRecord();
void updatePatientRecord();
void listPatientsByDisease();
void listPatientsByDoctor();
void listPatientsByBloodType();
void generateReport();
void inputPersonalDetails(PersonalDetails *personal);
void displayPersonalDetails(PersonalDetails personal);
void inputHealthDetails(HealthDetails *health);
void displayHealthDetails(HealthDetails health);
void inputTreatmentDetails(TreatmentDetails *treatment);
void displayTreatmentDetails(TreatmentDetails treatment);
void savePatientRecord(PatientRecord record);
void loadPatientRecords(FILE *file, PatientRecord *record);

int main()
	{
    mainMenu();
    return 0;
	}

void mainMenu() 
{
    int choice;

    do {
        printf("\n======================================\n");
        printf("       Hospital Management System:      \n");
        printf("======================================\n");
        printf("1. Register Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient by ID\n");
        printf("4. Delete Patient Record\n");
        printf("5. Update Patient Record\n");
        printf("6. List Patients by Disease\n");
        printf("7. List Patients by Doctor\n");
        printf("8. List Patients by Blood Type\n");
        printf("9. Generate Report\n");
        printf("10. Exit\n");
        printf("--------------------------------------\n");
        printf("Enter Your Choice... ");
        scanf("%d", &choice);

        switch (choice) 
		{
            case 1:
                registerPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                searchPatientByID();
                break;
            case 4:
                deletePatientRecord();
                break;
            case 5:
                updatePatientRecord();
                break;
            case 6:
                listPatientsByDisease();
                break;
            case 7:
                listPatientsByDoctor();
                break;
            case 8:
                listPatientsByBloodType();
                break;
            case 9:
                generateReport();
                break;
            case 10:
                printf("Exiting the system..\n Thank You!..\n");
                break;
            default:
                printf("Invalid Choice. Please try again.\n");
        }
    } while (choice != 10);
}

void registerPatient() 
	{
    PatientRecord record;

    printf("\n--- Register Patient ---\n");

    printf("\n--- Personal Details ---\n");
    inputPersonalDetails(&record.personal);
    
    printf("\n--- Health Details ---\n");
    inputHealthDetails(&record.health);
    
    printf("\n--- Treatment Details ---\n");
    inputTreatmentDetails(&record.treatment);

    savePatientRecord(record);
    printf("\nPatient Registered Successfully!!..\n");
	}

void viewPatients() 
	{
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("Error Opening File!!..\n");
        return;
    }

    PatientRecord record;

    printf("\n== = Patient Records = ==\n");
    while (fread(&record, sizeof(PatientRecord), 1, file)) 
	{
    	printf("\n--- Personal Details ---\n");
        displayPersonalDetails(record.personal);
    	printf("\n--- Health Details ---\n");
        displayHealthDetails(record.health);
    	printf("\n--- Treatment Details ---\n");
        displayTreatmentDetails(record.treatment);
    }

    fclose(file);
}

void searchPatientByID() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("Error Opening File!!\n");
        return;
    }

    int id, found = 0;
    PatientRecord record;

    printf("\nEnter Patient ID to Search... ");
    scanf("%d", &id);

    while (fread(&record, sizeof(PatientRecord), 1, file)) 
	{
        if (record.personal.id == id) 
		{
            printf("\n=== Patient Found ===\n");
            printf("\n--- Personal Details ---\n");
            displayPersonalDetails(record.personal);
            
            printf("\n--- Health Details ---\n");
            displayHealthDetails(record.health);
            
            printf("\n--- Treatment Details ---\n");
            displayTreatmentDetails(record.treatment);
            found = 1;
            break;
        }
    }

    if (!found) 
	{
        printf("\nPatient with ID %d Not Found...\n", id);
    }

    fclose(file);
}

void deletePatientRecord() 
{
    FILE *file = fopen(FILE_NAME, "rb");
    FILE *tempFile = fopen("temp.dat", "wb");
    if (!file || !tempFile) {
        printf("Error opening file!!\n");
        return;
    }

    int id, found = 0;
    PatientRecord record;

    printf("\nEnter Patient ID to Delete...");
    scanf("%d", &id);

    while (fread(&record, sizeof(PatientRecord), 1, file)) 
	{
        if (record.personal.id == id) 
		{
            found = 1;
            continue;
        }
        fwrite(&record, sizeof(PatientRecord), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) 
	{
        printf("\nPatient Record Deleted Successfully!!..\n");
    } 
	else 
	{
        printf("\nPatient with ID %d Not found...\n", id);
    }
}

void updatePatientRecord() 
	{
    FILE *file = fopen(FILE_NAME, "r+b");
    if (!file) 
	{
        printf("Error Opening File!!\n");
        return;
    }

	int id, found = 0;
    PatientRecord record;

    printf("\nEnter Patient ID to Update... ");
    scanf("%d", &id);

    while (fread(&record, sizeof(PatientRecord), 1, file))
	 {
        if (record.personal.id == id) 
		{
            found = 1;
            printf("\n--- Update Patient Details ---\n");
            printf("\n--- Personal Details ---\n");
            inputPersonalDetails(&record.personal);
            
            printf("\n--- Health Details ---\n");
            inputHealthDetails(&record.health);
            
            printf("\n--- Treatment Details ---\n");
            inputTreatmentDetails(&record.treatment);
            
            fwrite(&record, sizeof(PatientRecord), 1, file);
            printf("\nPatient Record Updated Successfully!!..\n");
            break;
        }
    }

    if (!found) 
	{
        printf("\nPatient with ID %d Not Found...\n", id);
    }

    fclose(file);
}

void listPatientsByDisease() 
	{
    char disease[50];
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) 
	{
        printf("Error Opening File!!\n");
        return;
    }

    printf("\nEnter the Disease to Search For... ");
    getchar(); 
    fgets(disease, sizeof(disease), stdin);
    disease[strcspn(disease, "\n")] = 0; 

    PatientRecord record;
    int found = 0;

    printf("\n--- Patients with Disease: %s ---\n", disease);
    while (fread(&record, sizeof(PatientRecord), 1, file)) 
	{
        if (strcmp(record.health.disease, disease) == 0) 
		{
        	printf("\n--- Personal Details ---\n");
            displayPersonalDetails(record.personal);
        	printf("\n--- Health Details ---\n");
            displayHealthDetails(record.health);
        	printf("\n--- Treatment Details ---\n");
            displayTreatmentDetails(record.treatment);
            found = 1;
        }
    }

    if (!found) 
	{
        printf("No Patients Found with the Disease '%s'.\n", disease);
    }

    fclose(file);
}

void listPatientsByDoctor() 
	{
    char doctor[50];
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) 
	{
        printf("Error Opening File!!\n");
        return;
    }

    printf("\nEnter the Doctor's Name to Search For... ");
    getchar();
    fgets(doctor, sizeof(doctor), stdin);
    doctor[strcspn(doctor, "\n")] = 0; 

    PatientRecord record;
    int found = 0;

    printf("\n--- Patients Treated by Doctor: %s ---\n", doctor);
    while (fread(&record, sizeof(PatientRecord), 1, file)) 
	{
        if (strcmp(record.treatment.doctor, doctor) == 0) 
		{
        	printf("\n--- Personal Details ---\n");
            displayPersonalDetails(record.personal);
        	printf("\n--- Health Details ---\n");
            displayHealthDetails(record.health);
        	printf("\n--- Treatment Details ---\n");
            displayTreatmentDetails(record.treatment);
            found = 1;
        }
    }

    if (!found) 
	{
        printf("No Patients Found Treated by Doctor '%s'.\n", doctor);
    }

    fclose(file);
}

void listPatientsByBloodType() 
	{
    char bloodType[5];
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) 
	{
        printf("Error Opening File!\n");
        return;
    }

    printf("\nEnter the Blood Type to Search For... ");
    getchar(); 
    fgets(bloodType, sizeof(bloodType), stdin);
    bloodType[strcspn(bloodType, "\n")] = 0;

    PatientRecord record;
    int found = 0;

    printf("\n--- Patients with Blood Type: %s ---\n", bloodType);
    while (fread(&record, sizeof(PatientRecord), 1, file)) 
	{
        if (strcmp(record.health.blood_type, bloodType) == 0) 
		{
        	printf("\n--- Personal Details ---\n");
            displayPersonalDetails(record.personal);
        	printf("\n--- Health Details ---\n");
            displayHealthDetails(record.health);
        	printf("\n--- Treatment Details ---\n");
            displayTreatmentDetails(record.treatment);
            found = 1;
        }
    }

    if (!found) 
	{
        printf("No Patients Found with Blood Type '%s'...\n", bloodType);
    }

    fclose(file);
}

void generateReport() 
	{
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) 
	{
        printf("Error Opening File!!\n");
        return;
    }

    PatientRecord record;
    int totalPatients = 0;
    float totalCost = 0;

    printf("\n--- Hospital Report ---\n");
    while (fread(&record, sizeof(PatientRecord), 1, file)) 
	{
        totalPatients++;
        totalCost += record.health.cost;
    }

    printf("Total Patients... %d\n", totalPatients);
    printf("Total Treatment Cost... %.2f\n", totalCost);

    fclose(file);
}

void inputPersonalDetails(PersonalDetails *personal) 
{
    printf("Enter Patient ID... ");
    scanf("%d", &personal->id);
    getchar();

    printf("Enter Name... ");
    fgets(personal->name, sizeof(personal->name), stdin);
    personal->name[strcspn(personal->name, "\n")] = 0;

    printf("Enter Age... ");
    scanf("%d", &personal->age);
    getchar();

    printf("Enter Gender (Male/Female)... ");
    fgets(personal->gender, sizeof(personal->gender), stdin);
    personal->gender[strcspn(personal->gender, "\n")] = 0;

    printf("Enter Contact...+92 ");
    fgets(personal->contact, sizeof(personal->contact), stdin);
    personal->contact[strcspn(personal->contact, "\n")] = 0;

    printf("Enter Address... ");
    fgets(personal->address, sizeof(personal->address), stdin);
    personal->address[strcspn(personal->address, "\n")] = 0;

    printf("Enter Email... ");
    fgets(personal->email, sizeof(personal->email), stdin);
    personal->email[strcspn(personal->email, "\n")] = 0;

    printf("Enter Marital Status... ");
    fgets(personal->marital_status, sizeof(personal->marital_status), stdin);
    personal->marital_status[strcspn(personal->marital_status, "\n")] = 0;

    printf("Enter Nationality... ");
    fgets(personal->nationality, sizeof(personal->nationality), stdin);
    personal->nationality[strcspn(personal->nationality, "\n")] = 0;

    printf("Enter Emergency Contact... ");
    fgets(personal->emergency_contact, sizeof(personal->emergency_contact), stdin);
    personal->emergency_contact[strcspn(personal->emergency_contact, "\n")] = 0;

    printf("Enter Insurance Number... ");
    fgets(personal->insurance_number, sizeof(personal->insurance_number), stdin);
    personal->insurance_number[strcspn(personal->insurance_number, "\n")] = 0;
}

void displayPersonalDetails(PersonalDetails personal) 
{
    printf("\nPatient ID... %d\n", personal.id);
    printf("Name... %s\n", personal.name);
    printf("Age... %d\n", personal.age);
    printf("Gender... %s\n", personal.gender);
    printf("Contact... %s\n", personal.contact);
    printf("Address... %s\n", personal.address);
    printf("Email... %s\n", personal.email);
    printf("Marital Status... %s\n", personal.marital_status);
    printf("Nationality... %s\n", personal.nationality);
    printf("Emergency Contact... %s\n", personal.emergency_contact);
    printf("Insurance Number... %s\n", personal.insurance_number);
}

void inputHealthDetails(HealthDetails *health) 
{
    printf("Enter Blood Type... ");
    fgets(health->blood_type, sizeof(health->blood_type), stdin);
    health->blood_type[strcspn(health->blood_type, "\n")] = 0;

    printf("Enter Disease... ");
    fgets(health->disease, sizeof(health->disease), stdin);
    health->disease[strcspn(health->disease, "\n")] = 0;

    printf("Enter Treatment Cost... ");
    scanf("%f", &health->cost);
    getchar();

    printf("Enter Allergies... ");
    fgets(health->allergies, sizeof(health->allergies), stdin);
    health->allergies[strcspn(health->allergies, "\n")] = 0;

    printf("Enter Medical History... ");
    fgets(health->medical_history, sizeof(health->medical_history), stdin);
    health->medical_history[strcspn(health->medical_history, "\n")] = 0;

    printf("Enter Medication... ");
    fgets(health->medication, sizeof(health->medication), stdin);
    health->medication[strcspn(health->medication, "\n")] = 0;

    printf("Enter Previous Surgeries... ");
    fgets(health->previous_surgeries, sizeof(health->previous_surgeries), stdin);
    health->previous_surgeries[strcspn(health->previous_surgeries, "\n")] = 0;

    printf("Enter Family History... ");
    fgets(health->family_history, sizeof(health->family_history), stdin);
    health->family_history[strcspn(health->family_history, "\n")] = 0;

    printf("Enter Height (in cm)... ");
    scanf("%d", &health->height);

    printf("Enter Weight (in kg)... ");
    scanf("%d", &health->weight);
    getchar();

    printf("Enter Smoking Status... ");
    fgets(health->smoking_status, sizeof(health->smoking_status), stdin);
    health->smoking_status[strcspn(health->smoking_status, "\n")] = 0;
}

void displayHealthDetails(HealthDetails health) 
{
    printf("Blood Type... %s\n", health.blood_type);
    printf("Disease... %s\n", health.disease);
    printf("Cost... %.2f\n", health.cost);
    printf("Allergies... %s\n", health.allergies);
    printf("Medical History... %s\n", health.medical_history);
    printf("Medication... %s\n", health.medication);
    printf("Previous Surgeries... %s\n", health.previous_surgeries);
    printf("Family History... %s\n", health.family_history);
    printf("Height... %d cm\n", health.height);
    printf("Weight... %d kg\n", health.weight);
    printf("Smoking Status... %s\n", health.smoking_status);
}

void inputTreatmentDetails(TreatmentDetails *treatment) 
{
    printf("Enter Treatment... ");
    fgets(treatment->treatment, sizeof(treatment->treatment), stdin);
    treatment->treatment[strcspn(treatment->treatment, "\n")] = 0;

    printf("Enter Doctor's Name... ");
    fgets(treatment->doctor, sizeof(treatment->doctor), stdin);
    treatment->doctor[strcspn(treatment->doctor, "\n")] = 0;

    printf("Enter Treatment Date (dd/mm/yyyy)... ");
    fgets(treatment->treatment_date, sizeof(treatment->treatment_date), stdin);
    treatment->treatment_date[strcspn(treatment->treatment_date, "\n")] = 0;

    printf("Enter Hospital Name... ");
    fgets(treatment->hospital_name, sizeof(treatment->hospital_name), stdin);
    treatment->hospital_name[strcspn(treatment->hospital_name, "\n")] = 0;

    printf("Enter Treatment Type... ");
    fgets(treatment->treatment_type, sizeof(treatment->treatment_type), stdin);
    treatment->treatment_type[strcspn(treatment->treatment_type, "\n")] = 0;

    printf("Enter Prescription... ");
    fgets(treatment->prescription, sizeof(treatment->prescription), stdin);
    treatment->prescription[strcspn(treatment->prescription, "\n")] = 0;

    printf("Enter Follow-up Date(dd/mm/yyyy)... ");
    fgets(treatment->follow_up_date, sizeof(treatment->follow_up_date), stdin);
    treatment->follow_up_date[strcspn(treatment->follow_up_date, "\n")] = 0;

    printf("Enter Doctor's Contact...+92 ");
    fgets(treatment->doctor_contact, sizeof(treatment->doctor_contact), stdin);
    treatment->doctor_contact[strcspn(treatment->doctor_contact, "\n")] = 0;

    printf("Enter Room Number... ");
    fgets(treatment->room_number, sizeof(treatment->room_number), stdin);
    treatment->room_number[strcspn(treatment->room_number, "\n")] = 0;

    printf("Enter Treatment Status... ");
    fgets(treatment->treatment_status, sizeof(treatment->treatment_status), stdin);
    treatment->treatment_status[strcspn(treatment->treatment_status, "\n")] = 0;

    printf("Enter Admission Date(dd/mm/yyyy)... ");
    fgets(treatment->admission_date, sizeof(treatment->admission_date), stdin);
    treatment->admission_date[strcspn(treatment->admission_date, "\n")] = 0;
}

void displayTreatmentDetails(TreatmentDetails treatment) 
{
    printf("Treatment... %s\n", treatment.treatment);
    printf("Doctor... %s\n", treatment.doctor);
    printf("Treatment Date... %s\n", treatment.treatment_date);
    printf("Hospital Name... %s\n", treatment.hospital_name);
    printf("Treatment Type... %s\n", treatment.treatment_type);
    printf("Prescription... %s\n", treatment.prescription);
    printf("Follow-up Date... %s\n", treatment.follow_up_date);
    printf("Doctor Contact: %s\n", treatment.doctor_contact);
    printf("Room Number... %s\n", treatment.room_number);
    printf("Treatment Status... %s\n", treatment.treatment_status);
    printf("Admission Date... %s\n", treatment.admission_date);
}

void savePatientRecord(PatientRecord record) 
{
    FILE *file = fopen(FILE_NAME, "ab");
    if (!file) 
	{
        printf("Error Opening File For Saving Patient Record!!\n");
        return;
    }
    fwrite(&record, sizeof(PatientRecord), 1, file);
    fclose(file);
}
