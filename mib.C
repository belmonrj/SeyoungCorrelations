Double_t myfun(Double_t *x, Double_t *p) {
 Double_t tot=p[0]*(1.0+2.0*p[1]*cos(x[0])+2.0*p[2]*cos(2.0*x[0]));
 return tot;
} // myfun
Double_t myfum(Double_t *x, Double_t *p) {
 Double_t ref=p[0]*(1.0+2.0*p[1]*cos(x[0])+2.0*p[2]*cos(2.0*x[0]))+p[3];
 Double_t tot=ref+(p[0]+p[3])*2.0*p[4]*cos(2.0*x[0]);
 return tot;
} // myfum
Double_t myfuo(Double_t *x, Double_t *p) {
 Double_t tot=p[0]*(1.0+2.0*p[2]*cos(2.0*x[0]))+p[1];
 return tot;
} // myfuo
void solve(int i12, int i13, int i23, double par[10][5][2], double per[10][5][2], double res[3][5][2], 
           int ii, TGraphErrors *tgg[10][3], TCanvas *tcc, int l1, int l2, int l3, int icol, int ityp) {
 float pp1[5],pp2[5],pp3[5],pe1[5],pe2[5],pe3[5],xx[5],xe[5];
 for (int ic=0; ic<5; ic++) {
  double p12=par[i12][ic][1]; double e12=per[i12][ic][1];
  double p13=par[i13][ic][1]; double e13=per[i13][ic][1];
  double p23=par[i23][ic][1]; double e23=per[i23][ic][1];
  double sgn=-1.0;
  if (p12>0 && p13>0 && p23>0) sgn=1.0;
  double p1=0.0; double e1=0.0;
  double p2=0.0; double e2=0.0;
  double p3=0.0; double e3=0.0;
  double dd=0.0;
  if (p12!=0 || p13!=0 || p23!=0) {
   dd=sqrt(pow(e12/p12,2.0)+pow(e13/p13,2.0)+pow(e23/p23,2.0));
   p1=sqrt(fabs(p12*p13/p23)); e1=p1*dd; p1=sgn*p1;
   p2=sqrt(fabs(p12*p23/p13)); e2=p2*dd; p2=sgn*p2;
   p3=sqrt(fabs(p13*p23/p12)); e3=p3*dd; p3=sgn*p3;
  } else {
   cout << "error" << endl;
  }
  res[0][ic][0]=p1; res[0][ic][1]=e1; pp1[ic]=p1; pe1[ic]=e1;
  res[1][ic][0]=p2; res[1][ic][1]=e2; pp2[ic]=p2; pe2[ic]=e2;
  res[2][ic][0]=p3; res[2][ic][1]=e3; pp3[ic]=p3; pe3[ic]=e3;
  xx[ic]=(ic+0.5)*20.0-2.5+0.5*(ii+0.5); xe[ic]=0.0;
 }
 tgg[ii][0] = new TGraphErrors(5,xx,pp1,xe,pe1);
 tgg[ii][1] = new TGraphErrors(5,xx,pp2,xe,pe2);
 tgg[ii][2] = new TGraphErrors(5,xx,pp3,xe,pe3);
 tgg[ii][0]->SetMarkerStyle(ityp); tgg[ii][0]->SetMarkerSize(0.8);
 tgg[ii][1]->SetMarkerStyle(ityp); tgg[ii][1]->SetMarkerSize(0.8);
 tgg[ii][2]->SetMarkerStyle(ityp); tgg[ii][2]->SetMarkerSize(0.8);
 tgg[ii][0]->SetMarkerColor(icol); tgg[ii][0]->SetLineColor(icol);
 tgg[ii][1]->SetMarkerColor(icol); tgg[ii][1]->SetLineColor(icol);
 tgg[ii][2]->SetMarkerColor(icol); tgg[ii][2]->SetLineColor(icol);
 tcc->cd(l1); tgg[ii][0]->Draw("p");
 tcc->cd(l2); tgg[ii][1]->Draw("p");
 tcc->cd(l3); tgg[ii][2]->Draw("p");
}
void mib(int ip=0) {
 cout << "pT id = " << ip << endl;
 TFile  *file[10];
 TH1D   *his;
 TH1D   *minb[10];
 TText  *tit[10];
 TText  *tjt[10];
 TF1    *ff[10][5],*fff[10][5];
 TF1    *fr[10][5],*ffr[10][5];
 TH1D   *hist[10];
 TLine  *line[10];
 TGraphErrors *tg[10][5];
 int    nbin;
 double xmin,xmax;
 double ave[100];
 double nor[100];
 double par[10][5][2],qar[10][5][2];
 double per[10][5][2],qer[10][5][2];
 double res[3][5][2];
 float x[5]={10.0,30.0,50.0,70.0,90.0};
 float y[5],ye[5],xe[5];
 TCanvas *tc = new TCanvas("tc","tc",10,30,1050,650);
 TCanvas *td = new TCanvas("td","td",30,30,1050,650);
 TCanvas *te = new TCanvas("te","te",50,30,1050,650);
 tc->Divide(5,2);
 td->Divide(5,2);
 te->Divide(5,2);
 for (int ii=0; ii<10; ii++) {
  tc->cd(ii+1);
  if (ii==0) file[ii] = TFile::Open("CorHisto_BBCN_BBCS.root");
  if (ii==1) file[ii] = TFile::Open("CorHisto_BBCN_FVTS.root");
  if (ii==2) file[ii] = TFile::Open("CorHisto_BBCN_FVTN.root");
  if (ii==3) file[ii] = TFile::Open("CorHisto_CNT_FVTS.root");
  if (ii==4) file[ii] = TFile::Open("CorHisto_CNT_FVTN.root");
  if (ii==5) file[ii] = TFile::Open("CorHisto_FVTN_FVTS.root");
  if (ii==6) file[ii] = TFile::Open("CorHisto_FVTN_BBCS.root");
  if (ii==7) file[ii] = TFile::Open("CorHisto_FVTS_BBCS.root");
  if (ii==8) file[ii] = TFile::Open("CorHisto_CNT_BBCS.root");
  if (ii==9) file[ii] = TFile::Open("CorHisto_CNT_BBCN.root");
  gROOT->ProcessLine(".ls");
  for (int i=0; i<100; i++) {
   ave[i]=0;
   nor[i]=0;
  }
  for (int i=0; i<4; i++) {
   if (ii==0) his = (TH1D*)gROOT->FindObject(Form("SIG_BBCN_BBCS_C%d",i));
   if (ii==1) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_BBCN_FVTS_C%d",i));
   if (ii==2) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_BBC_FVTN_C%d",i));
   if (ii==3) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_CNT_FVTS_C%d_pT%d",i,ip));
   if (ii==4) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_CNT_FVTN_C%d_pT%d",i,ip));
   if (ii==5) his = (TH1D*)gROOT->FindObject(Form("SIG_FVTN_FVTS_C%d",i));
   if (ii==6) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_BBCS_FVTN_C%d",i));
   if (ii==7) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_BBC_FVTS_C%d",i));
   if (ii==8) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_CNT_BBCS_C%d_pT%d",i,ip));
   if (ii==9) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_CNT_BBCN_C%d_pT%d",i,ip));
   if (i==0) {
    nbin=his->GetNbinsX();
    xmin=his->GetBinLowEdge(1);
    xmax=his->GetBinLowEdge(nbin)+his->GetBinWidth(nbin);
    minb[ii] = new TH1D(Form("minb%d",ii),"",nbin,xmin,xmax);
    minb[ii]->SetStats(0);
    minb[ii]->SetMinimum(0.949);
    minb[ii]->SetMaximum(1.051);
    minb[ii]->SetMarkerStyle(20);
    minb[ii]->SetMarkerSize(0.5);
    minb[ii]->SetMarkerColor(6);
    minb[ii]->SetLineColor(6);
    minb[ii]->SetLineWidth(1);
    minb[ii]->Draw();
    if (ii==0) tit[ii] = new TText(-1.0, 1.04, Form("BBC(N)-BBC(S)"));
    if (ii==1) tit[ii] = new TText(-1.0, 1.04, Form("BBC(N)-FVT(S)"));
    if (ii==2) tit[ii] = new TText(-1.0, 1.04, Form("BBC(N)-FVT(N)"));
    if (ii==3) tit[ii] = new TText(-1.0, 1.04, Form("CNT(%d)-FVT(S)",ip));
    if (ii==4) tit[ii] = new TText(-1.0, 1.04, Form("CNT(%d)-FVT(N)",ip));
    if (ii==5) tit[ii] = new TText(-1.0, 1.04, Form("FVT(N)-FVT(S)"));
    if (ii==6) tit[ii] = new TText(-1.0, 1.04, Form("BBC(S)-FVT(N)"));
    if (ii==7) tit[ii] = new TText(-1.0, 1.04, Form("BBC(S)-FVT(S)"));
    if (ii==8) tit[ii] = new TText(-1.0, 1.04, Form("CNT(%d)-BBC(S)",ip));
    if (ii==9) tit[ii] = new TText(-1.0, 1.04, Form("CNT(%d)-BBC(N)",ip));
    tit[ii]->SetTextSize(0.07);
    tit[ii]->Draw("same");
    cout << file[ii]->GetName() << " " << his->GetName() << " : ";
    cout << minb[ii]->GetName() << " " << tit[ii]->GetTitle() << " : ";
    cout << nbin << " : " << xmin << " " << xmax << endl;
    for (int k=0; k<5; k++) {
     ff[ii][k] = new TF1(Form("ff_%d_%d",ii,k),myfun,xmin,xmax,3);
     fff[ii][k] = new TF1(Form("fff_%d_%d",ii,k),myfuo,xmin,xmax,3);
     ff[ii][k]->SetLineWidth(1);
     fff[ii][k]->SetLineWidth(1);
     if (k<4) {ff[ii][k]->SetLineColor(k+1); fff[ii][k]->SetLineColor(k+1);} 
     else     {ff[ii][k]->SetLineColor(k+2); fff[ii][k]->SetLineColor(k+2);}
    }
    for (int k=0; k<5; k++) {
     fr[ii][k] = new TF1(Form("fr_%d_%d",ii,k),myfum,xmin,xmax,5);
     ffr[ii][k] = new TF1(Form("ffr_%d_%d",ii,k),myfuo,xmin,xmax,3);
     fr[ii][k]->SetLineWidth(1);
     ffr[ii][k]->SetLineWidth(1);
     if (k<4) {fr[ii][k]->SetLineColor(k+1); ffr[ii][k]->SetLineColor(k+1);}
     else     {fr[ii][k]->SetLineColor(k+2); ffr[ii][k]->SetLineColor(k+2);}
    }
   }
   for (int j=0; j<nbin; j++) {
    double val=his->GetBinContent(j+1);
    double err=his->GetBinError  (j+1);
    if (err>0) {
     ave[j]+=val/(err*err);
     nor[j]+=1.0/(err*err);
    } else {
     cout << "error cent=" << i << " bin=" << j << endl;
    }
   }
   his->SetLineWidth(1);
   his->SetLineColor(i+1);
   his->SetMarkerColor(i+1);
   his->SetMarkerStyle(24);
   his->SetMarkerSize(0.7);
   his->Draw("same");
   his->Fit(Form("ff_%d_%d",ii,i),"nq");
   ff[ii][i]->Draw("same");
   for (int j=0; j<3; j++) {
    printf("(%f,%f) ",ff[ii][i]->GetParameter(j),ff[ii][i]->GetParError(j));
   }
   printf("\n");
   par[ii][i][0]=ff[ii][i]->GetParameter(1);
   par[ii][i][1]=ff[ii][i]->GetParameter(2);
   per[ii][i][0]=ff[ii][i]->GetParError (1);
   per[ii][i][1]=ff[ii][i]->GetParError (2);
   fff[ii][i]->SetParameter(0,ff[ii][i]->GetParameter(0));
   fff[ii][i]->SetParameter(1,-0.04                     );
   fff[ii][i]->SetParameter(2,ff[ii][i]->GetParameter(2));
   fff[ii][i]->Draw("same");
  }
  for (int j=0; j<nbin; j++) {
   double val=0;
   double err=0;
   if (nor[j]>0) {
    val=ave[j]/nor[j];
    err=1.0/sqrt(nor[j]);
   } else {
    cout << "error bin=" << j << endl;
   }
   minb[ii]->SetBinContent(j+1,val);
   minb[ii]->SetBinError  (j+1,err);
  }
  minb[ii]->Fit(Form("ff_%d_%d",ii,4),"nq");
  ff[ii][4]->Draw("same");
  for (int j=0; j<3; j++) {
   printf("(%f,%f) ",ff[ii][4]->GetParameter(j),ff[ii][4]->GetParError(j));
  }
  printf("\n");
  par[ii][4][0]=ff[ii][4]->GetParameter(1);
  par[ii][4][1]=ff[ii][4]->GetParameter(2);
  per[ii][4][0]=ff[ii][4]->GetParError (1);
  per[ii][4][1]=ff[ii][4]->GetParError (2);
  fff[ii][4]->SetParameter(0,ff[ii][4]->GetParameter(0));
  fff[ii][4]->SetParameter(1,-0.04                     );
  fff[ii][4]->SetParameter(2,ff[ii][4]->GetParameter(2));
  fff[ii][4]->Draw("same");
  te->cd(ii+1);
  hist[ii] = new TH1D(Form("hist%d",ii),"",1,0,100);
  hist[ii]->SetStats(0);
  hist[ii]->SetMaximum(0.002);
  hist[ii]->SetMinimum(-0.002);
  hist[ii]->SetLineColor(1);
  hist[ii]->SetLineStyle(3);
  hist[ii]->Draw();
  line[ii] = new TLine(80.0,-0.002,80.0,0.002);
  line[ii]->SetLineStyle(3);
  line[ii]->Draw("same");
  for (int j=0; j<2; j++) {
   for (int i=0; i<5; i++) {
    if (j<1) {
     y [i]=ff[ii][i]->GetParameter(j+1)*0.1;
     ye[i]=ff[ii][i]->GetParError (j+1)*0.1;
    } else if (j<2) {
     y [i]=ff[ii][i]->GetParameter(j+1)*1.0;
     ye[i]=ff[ii][i]->GetParError (j+1)*1.0;
    } else {
     float y1 =ff[ii][i]->GetParameter(1);
     float y1e=ff[ii][i]->GetParError (1);
     float y2 =ff[ii][i]->GetParameter(2);
     float y2e=ff[ii][i]->GetParError (2);
     if (y1e>0 && y2e>0) {
      y [i]=-0.001*y2/y1;
      ye[i]=abs(y[i])*sqrt(pow(y1e/y1,2.0)+pow(y2e/y2,2.0));
     }
    }
    xe[i]=0.0;
   }
   tg[ii][j] = new TGraphErrors(5,x,y,xe,ye);
   tg[ii][j]->SetMarkerSize(0.8);
   tg[ii][j]->SetMarkerStyle(20);
   tg[ii][j]->SetMarkerColor(j+1);
   tg[ii][j]->SetLineColor(j+1);
   tg[ii][j]->Draw("psame");
  }
  td->cd(ii+1);
  minb[ii]->Draw();
  tit[ii]->Draw("same");
  for (int i=0; i<5; i++) {
   if (ii==0) his = (TH1D*)gROOT->FindObject(Form("SIG_BBCN_BBCS_C%d",i));
   if (ii==1) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_BBCN_FVTS_C%d",i));
   if (ii==2) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_BBC_FVTN_C%d",i));
   if (ii==3) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_CNT_FVTS_C%d_pT%d",i,ip));
   if (ii==4) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_CNT_FVTN_C%d_pT%d",i,ip));
   if (ii==5) his = (TH1D*)gROOT->FindObject(Form("SIG_FVTN_FVTS_C%d",i));
   if (ii==6) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_BBCS_FVTN_C%d",i));
   if (ii==7) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_BBC_FVTS_C%d",i));
   if (ii==8) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_CNT_BBCS_C%d_pT%d",i,ip));
   if (ii==9) his = (TH1D*)gROOT->FindObject(Form("SIG_COR_CNT_BBCN_C%d_pT%d",i,ip));
   if (i==4)  his = minb[ii];
   if (i==0) cout << file[ii]->GetName() << " " << his->GetName() << endl;
   his->Draw("same");
   fr[ii][i]->SetParameter(0,1.000000);
   fr[ii][i]->FixParameter(1,par[ii][3][0]);   // par[ii][3][0] c1 from peripheral
   fr[ii][i]->FixParameter(2,par[ii][3][1]);   // par[ii][4][1] c2 from min. bias
   fr[ii][i]->SetParameter(3,0.000000);
   fr[ii][i]->SetParameter(4,0.000000);
   his->Fit(Form("fr_%d_%d",ii,i),"nq");
   fr[ii][i]->Draw("same");
   for (int j=0; j<5; j++) {
    printf("(%f,%f) ",fr[ii][i]->GetParameter(j),fr[ii][i]->GetParError(j));
   }
   printf("\n");
   ffr[ii][i]->SetParameter(0,fr[ii][i]->GetParameter(0)+fr[ii][i]->GetParameter(3));
   ffr[ii][i]->SetParameter(1,-0.04                     );
   ffr[ii][i]->SetParameter(2,fr[ii][i]->GetParameter(4));
   ffr[ii][i]->Draw("same");
   qar[ii][i][0]=fr[ii][i]->GetParameter(3);
   qar[ii][i][1]=fr[ii][i]->GetParameter(4);
   qer[ii][i][0]=fr[ii][i]->GetParError (3);
   qer[ii][i][1]=fr[ii][i]->GetParError (4);
  }
  te->cd(ii+1);
  for (int j=3; j<5; j++) {
   for (int i=0; i<5; i++) {
    if (j<4) {
     y [i]=fr[ii][i]->GetParameter(4)*1.0;
     ye[i]=fr[ii][i]->GetParError (4)*1.0;
    } else {
     float y1 =fr[ii][i]->GetParameter(0);
     float y1e=fr[ii][i]->GetParError (0);
     float y2 =fr[ii][i]->GetParameter(3);
     float y2e=fr[ii][i]->GetParError (3);
     if (y1e>0 && y2e>0) {
      y [i]=0.002*y2;
      ye[i]=0.002*y2e;
     }
    }
    xe[i]=0.0;
   }
   tg[ii][j] = new TGraphErrors(5,x,y,xe,ye);
   tg[ii][j]->SetMarkerSize(1.0);
   if (j==3) { tg[ii][j]->SetMarkerStyle(24); tg[ii][j]->SetMarkerColor(4); tg[ii][j]->SetLineColor(4); }
   else      { tg[ii][j]->SetMarkerStyle(25); tg[ii][j]->SetMarkerColor(3); tg[ii][j]->SetLineColor(3); }
   tg[ii][j]->Draw("psame");
  }
  if (ii==0) tjt[ii] = new TText(7.0,-0.0017, Form("BBC(N)-BBC(S)"));
  if (ii==1) tjt[ii] = new TText(7.0,-0.0017, Form("BBC(N)-FVT(S)"));
  if (ii==2) tjt[ii] = new TText(7.0,-0.0017, Form("BBC(N)-FVT(N)"));
  if (ii==3) tjt[ii] = new TText(7.0,-0.0017, Form("CNT(%d)-FVT(S)",ip));
  if (ii==4) tjt[ii] = new TText(7.0,-0.0017, Form("CNT(%d)-FVT(N)",ip));
  if (ii==5) tjt[ii] = new TText(7.0,-0.0017, Form("FVT(N)-FVT(S)"));
  if (ii==6) tjt[ii] = new TText(7.0,-0.0017, Form("BBC(S)-FVT(N)"));
  if (ii==7) tjt[ii] = new TText(7.0,-0.0017, Form("BBC(S)-FVT(S)"));
  if (ii==8) tjt[ii] = new TText(7.0,-0.0017, Form("CNT(%d)-BBC(S)",ip));
  if (ii==9) tjt[ii] = new TText(7.0,-0.0017, Form("CNT(%d)-BBC(N)",ip));
  tjt[ii]->SetTextSize(0.07);
  tjt[ii]->Draw("same");
 }
 TCanvas *tcc = new TCanvas("tcc","tcc",50,50,1000,650);
 tcc->Divide(5,2);
 TH1D *hit = new TH1D("hit","",1,0,100);
 hit->SetStats(0);
 hit->SetMaximum( 0.15);
 hit->SetMinimum(-0.05);
 hit->SetLineColor(1);
 hit->SetLineStyle(3);
 for (int i=0; i<10; i++) {tcc->cd(i+1); hit->Draw();}
 TGraphErrors *tgg[10][3],*tqq[10][3];
 solve(3,4,5,par,per,res,0,tgg,tcc,  3,  2,  4,  1,20); // CNT FVT(S) FVT(N)
 solve(8,9,0,par,per,res,1,tgg,tcc,  3,  1,  5,  1,21); // CNT BBC(S) BBC(N)
 solve(3,8,7,par,per,res,2,tgg,tcc,  3,  2,  1,  2,20); // CNT FVT(S) BBC(S)
 solve(3,9,1,par,per,res,3,tgg,tcc,  3,  2,  5,  1,24); // CNT FVT(S) BBC(N)
 solve(4,8,6,par,per,res,4,tgg,tcc,  3,  4,  1,  1,25); // CNT FVT(N) BBC(S)
 solve(4,9,2,par,per,res,5,tgg,tcc,  3,  4,  5,  4,20); // CNT FVT(N) BBC(N)
 solve(5,7,6,par,per,res,6,tgg,tcc,  2,  4,  1,  2,24); // FVT(S) FVT(N) BBC(S)
 solve(5,1,2,par,per,res,7,tgg,tcc,  2,  4,  5,  4,24); // FVT(S) FVT(N) BBC(N)
 solve(0,7,1,par,per,res,8,tgg,tcc,  1,  5,  2,  2,25); // BBC(S) BBC(N) FVT(S)
 solve(0,6,2,par,per,res,9,tgg,tcc,  1,  5,  4,  4,25); // BBC(S) BBC(N) FVT(N)
// ***** after subtraction ***** //
 solve(3,4,5,qar,qer,res,0,tqq,tcc,5+3,5+2,5+4,  1,20); // CNT FVT(S) FVT(N)
 solve(8,9,0,qar,qer,res,1,tqq,tcc,5+3,5+1,5+5,  1,21); // CNT BBC(S) BBC(N)
 solve(3,8,7,qar,qer,res,2,tqq,tcc,5+3,5+2,5+1,  2,20); // CNT FVT(S) BBC(S)
 solve(3,9,1,qar,qer,res,3,tqq,tcc,5+3,5+2,5+5,  1,24); // CNT FVT(S) BBC(N)
 solve(4,8,6,qar,qer,res,4,tqq,tcc,5+3,5+4,5+1,  1,25); // CNT FVT(N) BBC(S)
 solve(4,9,2,qar,qer,res,5,tqq,tcc,5+3,5+4,5+5,  4,20); // CNT FVT(N) BBC(N)
 solve(5,7,6,qar,qer,res,6,tqq,tcc,5+2,5+4,5+1,  2,24); // FVT(S) FVT(N) BBC(S)
 solve(5,1,2,qar,qer,res,7,tqq,tcc,5+2,5+4,5+5,  4,24); // FVT(S) FVT(N) BBC(N)
 solve(0,7,1,qar,qer,res,8,tqq,tcc,5+1,5+5,5+2,  2,25); // BBC(S) BBC(N) FVT(S)
 solve(0,6,2,qar,qer,res,9,tqq,tcc,5+1,5+5,5+4,  4,25); // BBC(S) BBC(N) FVT(N)
}
