**1NF** - a single cell must not hold more than 1 value, there must be a primary key for identification, no duplicated rows and columns, each column must have only one value for each row in the table.

| ID | Patient | Patient address | Appointment date | Appointment time | Room | Price | Physician | Appointment cause |
| :--: | :-------: | :---------------: | :----------------: | :----------------: | :----: | :-----: | :---------: | :-----------------: |
| 1 | Jan Kot | 6 Dolna Street, 44-444 Bór | 2029-02-01 | 12:30 | 12 | 300 zł | Oleg Wyrwiząb | Dental: Denture fitting in (...) |
| 2 | Maria Mysz | 9 Górna Street, 55-555 Las | 2030-01-04 | 11:45 | 7 | 150 zł | Ewa Ciarka | Dermatology: Birthmark inspection (...) |

**2NF** - already 1NF, but has no partial dependency (all non-key attributes are fully dependent on a primary key).

| PatientID | Name | Address |
|:-: | :--: | :-----: |
| 1  | Jan Kot | 6 Dolna Street, 44-444 Bór |
| 2 | Maria Mysz | 9 Górna Street, 55-555 Las |

| PhysicianID | Name |
| :---------: | :--: |
| 1 | Oleg Wyrwiąg |
| 2 | Ewa Ciarka |

| AppointmentID | PatientID | PhysicianID | Date | Time | Room | Price | Appointment cause |
| :-----------: | :-------: | :---------: | :--: | :--: | :--: | :---: | :---------------: |
| 1 | 1 | 1 | 2029-02-01 | 12:30 | 12 | 300 zł | Dental: Denture fitting in (...) |
| 2 | 2 | 2 | 2030-01-04 | 11:45 | 7 | 150 zł | Dermatology: Birthmark inspection (...) |

**3NF** - already in 2NF, but no transitive partial dependency.

The current table in 2NF also meets the requirements of 3NF form, so there is no need for modifying it.