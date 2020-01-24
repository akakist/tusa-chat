-- MySQL dump 10.11
--
-- Host: localhost    Database: chat
-- ------------------------------------------------------
-- Server version	5.0.33-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `nn`
--

DROP TABLE IF EXISTS `nn`;
CREATE TABLE `nn` (
 `ID` int(10) unsigned NOT NULL auto_increment,
   
  `Nick` varchar(17) NOT NULL default '',
  `str_nick` varchar(17) NOT NULL default '',
  `Banned` int(2) default NULL,
  `uid` int(10) NOT NULL default '0',
  `bby` int(10) NOT NULL default '0',
  `last_usage_date` datetime NOT NULL default '2000-01-01 00:00:00',
  `ready_to_sale` char(1) NOT NULL default '0',
  `reserved_to_date` datetime NOT NULL default '2005-01-01 00:00:00',
  `cost` double NOT NULL default '0',
  PRIMARY KEY  (`ID`),
  KEY `_nick` (`Nick`),
  KEY `uidk` (`uid`),
  KEY `uppernick_key` (`str_nick`),
  KEY `banned_key` (`Banned`),
  KEY `ready_to_sale` (`ready_to_sale`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251;

