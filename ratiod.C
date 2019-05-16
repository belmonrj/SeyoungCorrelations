void ratiod()
{

  const int ntypes = 6;
  const int nlowmult = 2;
  const int nptbins = 6;

  double ptvalues[nptbins] = {0.35,0.7,1.2,1.7,2.35};

  string handle[ntypes];
  handle[0] = "CNT_BBCN_BBCS";
  handle[1] = "CNT_BBCN_FVTN";
  handle[2] = "CNT_BBCN_FVTS";
  handle[3] = "CNT_BBCS_FVTN";
  handle[4] = "CNT_BBCS_FVTS";
  handle[5] = "CNT_FVTN_FVTS";

  //double pt[nlowmult][ntypes][nptbins];
  double v2_raw[nlowmult][ntypes][nptbins];
  double ev2_raw[nlowmult][ntypes][nptbins];
  double v2_subA[nlowmult][ntypes][nptbins];
  double ev2_subA[nlowmult][ntypes][nptbins];
  double v2_subAZ[nlowmult][ntypes][nptbins];
  double ev2_subAZ[nlowmult][ntypes][nptbins];
  double v2_subRZ[nlowmult][ntypes][nptbins];
  double ev2_subRZ[nlowmult][ntypes][nptbins];
  double v2_subR[nlowmult][ntypes][nptbins];
  double ev2_subR[nlowmult][ntypes][nptbins];

  ifstream fin;
  for ( int ilowmult = 0; ilowmult < nlowmult; ++ilowmult )
    {
      for ( int itype = 0; itype < ntypes; ++itype )
        {
          int ptstop = nptbins;
          char fin_name[50];
          sprintf ( fin_name, "data_%s.txt", handle[itype].c_str() );
          if ( ilowmult == 1 )
            {
              ptstop = 5;
              sprintf ( fin_name, "data_ppref_%s.txt", handle[itype].c_str() );
            }
          cout << fin_name << endl;
          fin.open(fin_name);
          for ( int ipt = 0; ipt < ptstop; ++ipt )
            {
              //cout << ilowmult << " " << itype << " " << ipt << endl;
              double x;
              fin >> x
                  >> v2_raw[ilowmult][itype][ipt]   >> ev2_raw[ilowmult][itype][ipt]
                  >> v2_subA[ilowmult][itype][ipt]  >> ev2_subA[ilowmult][itype][ipt]
                  >> v2_subAZ[ilowmult][itype][ipt] >> ev2_subAZ[ilowmult][itype][ipt]
                  >> v2_subRZ[ilowmult][itype][ipt] >> ev2_subRZ[ilowmult][itype][ipt]
                  >> v2_subR[ilowmult][itype][ipt]  >> ev2_subR[ilowmult][itype][ipt];
              //cout << ptvalues[ipt] << " " << x << endl;
            } // loop over pt values
          fin.close();
        } // loop over types
    } // loop over low mult ref

  cout << "Got the data..." << endl;

  // ---

  TCanvas* c1 = new TCanvas("c1","");
  TH2D* hdummy = new TH2D("hdummy","",1,0.0,4.0,1,0.0,2.0);
  hdummy->Draw();

  double lmratio_raw[ntypes][nptbins];
  double elmratio_raw[ntypes][nptbins];
  double lmratio_subR[ntypes][nptbins];
  double elmratio_subR[ntypes][nptbins];
  TGraphErrors* tge_lmratio_raw[ntypes];
  TGraphErrors* tge_lmratio_subR[ntypes];
  cout << "starting type loop" << endl;
  for ( int itype = 0; itype < ntypes; ++itype )
    {
      cout << "starting pt loop" << endl;
      for ( int ipt = 0; ipt < nptbins-1; ++ipt )
        {
          lmratio_raw[itype][ipt] = v2_raw[0][itype][ipt]/v2_raw[1][itype][ipt];
          lmratio_subR[itype][ipt] = v2_subR[0][itype][ipt]/v2_subR[1][itype][ipt];
          elmratio_raw[itype][ipt] = 0; // do this later
          elmratio_subR[itype][ipt] = 0; // do this later
          cout << "calculated ratio " << v2_raw[0][itype][ipt] << "/" << v2_raw[1][itype][ipt] << " = " << lmratio_raw[itype][ipt] << endl;
          cout << "calculated ratio " << v2_subR[0][itype][ipt] << "/" << v2_subR[1][itype][ipt] << " = " << lmratio_subR[itype][ipt] << endl;
        }
      tge_lmratio_raw[itype] = new TGraphErrors(nptbins-1,ptvalues,lmratio_raw[itype],0,elmratio_raw[itype]);
      tge_lmratio_raw[itype]->SetMarkerStyle(itype);
      tge_lmratio_raw[itype]->SetMarkerColor(itype);
      //tge_lmratio_raw[itype]->Draw("p");
      tge_lmratio_subR[itype] = new TGraphErrors(nptbins-1,ptvalues,lmratio_subR[itype],0,elmratio_subR[itype]);
      tge_lmratio_subR[itype]->SetMarkerStyle(itype);
      tge_lmratio_subR[itype]->SetMarkerColor(itype);
      tge_lmratio_subR[itype]->Draw("p");
    }
  c1->Print("testfig.png");

}
