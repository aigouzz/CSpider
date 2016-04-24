#include<cspider/spider.h>

void p(cspider_t *cspider, char *d, void *user_data) {
  
  char *get[10];
  int size = xpath(d, "//body/div[@class='wrap']/div[@class='sort-column area']/div[@class='column-bd cfix']/ul[@class='st-list cfix']/li/strong/a", get, 10);
    
  int i;
  for (i = 0; i < size; i++) {
    saveString(cspider, get[i]);
  }
  
}

void s(void *str, void *user_data) {
  char *get = (char *)str;
  FILE *file = (FILE*)user_data;
  fprintf(file, "%s\n", get);
  return;
}

int main() {
  
  cspider_t *spider = init_cspider();
  char *agent = "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.110 Safari/537.36";
  //char *cookie = "bid=s3/yuH5Jd/I; ll=108288; viewed=1130500_24708145_6433169_4843567_1767120_5318823_1899158_1271597; __utma=30149280.927537245.1446813674.1446983217.1449139583.4; __utmz=30149280.1449139583.4.4.utmcsr=accounts.douban.com|utmccn=(referral)|utmcmd=referral|utmcct=/login; ps=y; ue=965166527@qq.com; dbcl2=58742090:QgZ2PSLiDLQ; ck=T9Wn; push_noty_num=0; push_doumail_num=7; ap=1; __utmb=30149280.0.10.1449139583; __utmc=30149280";
  
  cs_setopt_url(spider, "so.tv.sohu.com/list_p1100_p20_p3_u5185_u5730_p40_p5_p6_p77_p80_p9_2d1_p101_p11.html");
  
  cs_setopt_useragent(spider, agent);
  //cs_setopt_cookie(spider, cookie);
  cs_setopt_process(spider, p, NULL);
  cs_setopt_save(spider, s, stdout);
  cs_setopt_threadnum(spider, DOWNLOAD, 2);
  cs_setopt_threadnum(spider, SAVE, 2);
  //FILE *fp = fopen("log", "wb+");
  //cs_setopt_logfile(spider, fp);
  return cs_run(spider);
}
