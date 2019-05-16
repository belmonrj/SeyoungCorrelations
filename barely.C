void barely()
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
          char* fin_name;
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

  for ( int itype = 0; itype < ntypes; ++itype )
    {
      for ( int ipt = 0; ipt < nptbins; ++ipt )
        {
          if ( itype != 5 )
            {
              cout << handle[itype] << "/" << handle[5] << " "
                   << v2_raw[0][itype][ipt]/v2_raw[0][5][ipt] << " "
                   << v2_subR[0][itype][ipt]/v2_subR[0][5][ipt] << " "
                   << endl;
            }
          // --- done with pt loop
        } // loop over pt bins
    } // loop over types

  for ( int itype = 0; itype < ntypes; ++itype )
    {
      for ( int ipt = 0; ipt < nptbins; ++ipt )
        {
          // --- calculate the lm ratio
          if ( ipt < 5 )
            {
              cout << handle[itype] << " " << ptvalues[ipt] << " "
                   << v2_subR[0][itype][ipt] << "/" << v2_subR[1][itype][ipt] << " = "
                   << v2_subR[0][itype][ipt]/v2_subR[1][itype][ipt] << endl;
            } // check on pt for ratio
          // --- done with pt loop
        } // loop over pt bins
    } // loop over types

}
