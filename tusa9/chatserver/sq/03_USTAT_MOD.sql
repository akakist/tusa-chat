alter table users add column   `stat_last_date` datetime NOT NULL default '2006-01-01 00:00:00';
alter table users add column   `stat_last_ip` text NOT NULL;
alter table users add column   `stat_v_count` int(11) NOT NULL default '0';
alter table users add column   `stat_m_count` int(10) NOT NULL default '0';
alter table users add column   `stat_t_count` int(10) NOT NULL default '0';
alter table users add column   `kick_count` int(10) unsigned NOT NULL default '0';
alter table users add column   `kicked_count` int(10) unsigned NOT NULL default '0';

