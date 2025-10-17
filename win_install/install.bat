@echo off
chcp 65001 > nul
setlocal enabledelayedexpansion

echo ===============================================
echo                  CREATE DB
echo ===============================================

set DEFAULT_MYSQL_DIR=C:\Program Files\MariaDB 10.11\bin
set DB_NAME=isotopes_db
set DB_USER=isotope_user
set DB_HOST=localhost
set DB_PORT=3306
set DB_PASS=1234



set /p MYSQL_DIR="Enter path to MariaDB installation [%DEFAULT_MYSQL_DIR%]: "
if "!MYSQL_DIR!"=="" set MYSQL_DIR=%DEFAULT_MYSQL_DIR%

set MYSQL_EXE="!MYSQL_DIR!\mysql.exe"
set MYSQLADMIN_EXE="!MYSQL_DIR!\mysqladmin.exe"

if not exist !MYSQL_EXE! (
    echo Error: file mysql.exe does not exists in !MYSQL_DIR!
    echo Install MariaDB and set correct path
    pause
    exit /b 1
)

set /p DB_ROOT_USER="Root username [root]: "
if "!DB_ROOT_USER!"=="" set DB_ROOT_USER=root

set /p DB_ROOT_PASS="Root passwd: "

echo Connecting to MariaDB...
%MYSQLADMIN_EXE% -h %DB_HOST% -P %DB_PORT% -u %DB_ROOT_USER% -p%DB_ROOT_PASS% ping > nul 2>&1

if errorlevel 1 (
  echo Error occured while connecting to MariaDB
  exit /b 1 
)

echo Connected sucsessfully

echo Creating database '%DB_NAME%'...
%MYSQL_EXE% -h %DB_HOST% -P %DB_PORT% -u %DB_ROOT_USER% -p%DB_ROOT_PASS% -e "CREATE DATABASE IF NOT EXISTS %DB_NAME% CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;" 2>nul

if errorlevel 1 (
  echo Error occured while creating database
  exit /b 1
)

echo Database created sucsessfully

echo Creating user '%DB_USER%'

%MYSQL_EXE% -h %DB_HOST% -P %DB_PORT% -u %DB_ROOT_USER% -p%DB_ROOT_PASS% -e "CREATE USER IF NOT EXISTS '%DB_USER%'@'localhost' IDENTIFIED BY '%DB_PASS%';" 2>nul
%MYSQL_EXE% -h %DB_HOST% -P %DB_PORT% -u %DB_ROOT_USER% -p%DB_ROOT_PASS% -e "CREATE USER IF NOT EXISTS '%DB_USER%'@'%%' IDENTIFIED BY '%DB_PASS%';" 2>nul

%MYSQL_EXE% -h %DB_HOST% -P %DB_PORT% -u %DB_ROOT_USER% -p%DB_ROOT_PASS% -e "GRANT ALL PRIVILEGES ON %DB_NAME%.* TO '%DB_USER%'@'localhost';" 2>nul
%MYSQL_EXE% -h %DB_HOST% -P %DB_PORT% -u %DB_ROOT_USER% -p%DB_ROOT_PASS% -e "GRANT ALL PRIVILEGES ON %DB_NAME%.* TO '%DB_USER%'@'%%';" 2>nul
%MYSQL_EXE% -h %DB_HOST% -P %DB_PORT% -u %DB_ROOT_USER% -p%DB_ROOT_PASS% -e "FLUSH PRIVILEGES;" 2>nul

if errorlevel 1 (
  echo Error occured while creating user
  exit /b 1
)

echo Creating table 'isotopes'
%MYSQL_EXE% -h %DB_HOST% -P %DB_PORT% -u %DB_ROOT_USER% -p%DB_ROOT_PASS% %DB_NAME% < "%~dp0create_tables.sql" 2>nul

if errorlevel 1 (
  echo Error occured while creating table
  exit /b 1
)

echo.
echo ===============================================
echo           БАЗА ДАННЫХ УСПЕШНО СОЗДАНА
echo ===============================================
echo Database name:   %DB_NAME%
echo User:            %DB_USER%
echo Passwd:          %DB_PASS%
echo Host:            %DB_HOST%
echo Port:            %DB_PORT%
echo ===============================================

goto :eof
