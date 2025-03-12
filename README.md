# ipc-shared-memory
Файл main.c создает разделяемую память и семафоры, инициализирует строку "Hello". Он управляет синхронизацией процессов, следит за вводом "quit" для удаления ресурсов и завершения работы.
Файл writer.c подключается к разделяемой памяти и записывает в нее данные, блокируя семафорами доступ читателя во время записи. После ввода данных разблокирует чтение.
Файл reader.c ждет, пока данные будут записаны, затем читает их из памяти и выводит на экран. Использует семафоры для управления очередностью доступа.  

The `main.c` file creates shared memory and semaphores, initializing the string "Hello". It manages process synchronization and monitors the input for "quit" to remove resources and terminate execution.  

The `writer.c` file connects to shared memory and writes data to it, using semaphores to block reader access during writing. After input is provided, it unlocks reading.  

The `reader.c` file waits for data to be written, then reads it from memory and prints it to the screen. It uses semaphores to control access order.
