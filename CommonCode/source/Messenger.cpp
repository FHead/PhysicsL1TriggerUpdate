#include "Messenger.h"

L1NTupleMessenger::L1NTupleMessenger(TFile &File, string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   
   Event = NULL;
   GCT = NULL;
   Generator = NULL;
   Simulation = NULL;
   GMT = NULL;
   GT = NULL;
   RCT = NULL;
   DTTF = NULL;
   CALO = NULL;

   SetBranchAddress();
}

L1NTupleMessenger::~L1NTupleMessenger()
{
}

void L1NTupleMessenger::SetBranchAddress()
{
   if(Tree == NULL)
      return;

   Tree->SetBranchAddress("Event", &Event);
   Tree->SetBranchAddress("GCT", &GCT);
   Tree->SetBranchAddress("Generator", &Generator);
   Tree->SetBranchAddress("Simulation", &Simulation);
   Tree->SetBranchAddress("GMT", &GMT);
   Tree->SetBranchAddress("GT", &GT);
   Tree->SetBranchAddress("RCT", &RCT);
   Tree->SetBranchAddress("DTTF", &DTTF);
   Tree->SetBranchAddress("CALO", &CALO);
}

bool L1NTupleMessenger::GetEntry(int Entry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(Entry);

   GenP.clear();
   GenID.clear();
   GenStatus.clear();

   if(Generator != NULL)
   {
      for(int i = 0; i < (int)Generator->id.size(); i++)
      {
         FourVector P;
         P[0] = Generator->e[i];
         P[1] = Generator->px[i];
         P[2] = Generator->py[i];
         P[3] = Generator->pz[i];
         GenP.push_back(P);

         GenID.push_back(Generator->id[i]);

         GenStatus.push_back(Generator->status[i]);
      }
   }

   return true;
}

L1ExtraUpgradeTreeMessenger::L1ExtraUpgradeTreeMessenger(TFile &File, string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());

   L1ExtraUpgrade = NULL;

   SetBranchAddress();
}

L1ExtraUpgradeTreeMessenger::~L1ExtraUpgradeTreeMessenger()
{
}
   
void L1ExtraUpgradeTreeMessenger::SetBranchAddress()
{
   if(Tree == NULL)
      return;

   Tree->SetBranchAddress("L1ExtraUpgrade", &L1ExtraUpgrade);
}

bool L1ExtraUpgradeTreeMessenger::GetEntry(int Entry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(Entry);

   vector<double> D0;
   vector<int> I0;

   FillObject(EG, L1ExtraUpgrade->nEG, &L1ExtraUpgrade->egEt, &L1ExtraUpgrade->egEta, &L1ExtraUpgrade->egPhi, &L1ExtraUpgrade->egBx, &D0, &D0, &D0);
   FillObject(IsoEG, L1ExtraUpgrade->nIsoEG, &L1ExtraUpgrade->isoEGEt, &L1ExtraUpgrade->isoEGEta, &L1ExtraUpgrade->isoEGPhi, &L1ExtraUpgrade->isoEGBx, &D0, &D0, &D0);
   FillObject(TkEG, L1ExtraUpgrade->nTkEG, &L1ExtraUpgrade->tkEGEt, &L1ExtraUpgrade->tkEGEta, &L1ExtraUpgrade->tkEGPhi, &L1ExtraUpgrade->tkEGBx, &L1ExtraUpgrade->tkEGTrkIso, &L1ExtraUpgrade->tkEGzVtx, &D0);
   FillObject(TkEG2, L1ExtraUpgrade->nTkEG2, &L1ExtraUpgrade->tkEG2Et, &L1ExtraUpgrade->tkEG2Eta, &L1ExtraUpgrade->tkEG2Phi, &L1ExtraUpgrade->tkEG2Bx, &L1ExtraUpgrade->tkEG2TrkIso, &L1ExtraUpgrade->tkEG2zVtx, &D0);
   FillObject(TkIsoEG, L1ExtraUpgrade->nTkIsoEG, &L1ExtraUpgrade->tkIsoEGEt, &L1ExtraUpgrade->tkIsoEGEta, &L1ExtraUpgrade->tkIsoEGPhi, &L1ExtraUpgrade->tkIsoEGBx, &L1ExtraUpgrade->tkIsoEGTrkIso, &L1ExtraUpgrade->tkIsoEGzVtx, &D0);
   FillObject(TkEM, L1ExtraUpgrade->nTkEM, &L1ExtraUpgrade->tkEMEt, &L1ExtraUpgrade->tkEMEta, &L1ExtraUpgrade->tkEMPhi, &L1ExtraUpgrade->tkEMBx, &L1ExtraUpgrade->tkEMTrkIso, &D0, &D0);
   FillObject(Tau, L1ExtraUpgrade->nTau, &L1ExtraUpgrade->tauEt, &L1ExtraUpgrade->tauEta, &L1ExtraUpgrade->tauPhi, &L1ExtraUpgrade->tauBx, &D0, &D0, &D0);
   FillObject(IsoTau, L1ExtraUpgrade->nIsoTau, &L1ExtraUpgrade->isoTauEt, &L1ExtraUpgrade->isoTauEta, &L1ExtraUpgrade->isoTauPhi, &L1ExtraUpgrade->isoTauBx, &D0, &D0, &D0);
   FillObject(TkTau, L1ExtraUpgrade->nTkTau, &L1ExtraUpgrade->tkTauEt, &L1ExtraUpgrade->tkTauEta, &L1ExtraUpgrade->tkTauPhi, &L1ExtraUpgrade->tkTauBx, &L1ExtraUpgrade->tkTauTrkIso, &L1ExtraUpgrade->tkTauzVtx, &D0);
   FillObject(Jet, L1ExtraUpgrade->nJets, &L1ExtraUpgrade->jetEt, &L1ExtraUpgrade->jetEta, &L1ExtraUpgrade->jetPhi, &L1ExtraUpgrade->jetBx, &D0, &D0, &D0);
   FillObject(TkJet, L1ExtraUpgrade->nTkJets, &L1ExtraUpgrade->tkJetEt, &L1ExtraUpgrade->tkJetEta, &L1ExtraUpgrade->tkJetPhi, &L1ExtraUpgrade->tkJetBx, &D0, &L1ExtraUpgrade->tkJetzVtx, &D0);
   FillObject(FwdJet, L1ExtraUpgrade->nFwdJets, &L1ExtraUpgrade->fwdJetEt, &L1ExtraUpgrade->fwdJetEta, &L1ExtraUpgrade->fwdJetPhi, &L1ExtraUpgrade->fwdJetBx, &D0, &D0, &D0);

   FillObject(Muon, L1ExtraUpgrade->nMuons, &L1ExtraUpgrade->muonEt, &L1ExtraUpgrade->muonEta, &L1ExtraUpgrade->muonPhi, &L1ExtraUpgrade->muonBx, &D0, &D0, &D0);
   // vector<int>     muonChg;
   // vector<unsigned int> muonIso;
   // vector<unsigned int> muonFwd;
   // vector<unsigned int> muonMip;
   // vector<unsigned int> muonRPC;
   // vector<int>     muonQuality;
   
   FillObject(TkMuon, L1ExtraUpgrade->nTkMuons, &L1ExtraUpgrade->tkMuonEt, &L1ExtraUpgrade->tkMuonEta, &L1ExtraUpgrade->tkMuonPhi, &L1ExtraUpgrade->tkMuonBx, &L1ExtraUpgrade->tkMuonTrkIso, &L1ExtraUpgrade->tkMuonzVtx, &D0);
   // vector<int>     tkMuonChg;
   // vector<unsigned int> tkMuonIso;
   // vector<unsigned int> tkMuonFwd;
   // vector<unsigned int> tkMuonMip;
   // vector<unsigned int> tkMuonRPC;
   // vector<unsigned int> tkMuonQuality;

   FillObject(MET, L1ExtraUpgrade->nMet, &L1ExtraUpgrade->met, &D0, &L1ExtraUpgrade->metPhi, &L1ExtraUpgrade->metBx, &D0, &D0, &L1ExtraUpgrade->et);
   FillObject(TkMET, L1ExtraUpgrade->nTkMet, &L1ExtraUpgrade->tkMet, &D0, &L1ExtraUpgrade->tkMetPhi, &L1ExtraUpgrade->tkMetBx, &D0, &D0, &L1ExtraUpgrade->tkEt);
   FillObject(MHT, L1ExtraUpgrade->nMht, &L1ExtraUpgrade->mht, &D0, &L1ExtraUpgrade->mhtPhi, &L1ExtraUpgrade->mhtBx, &D0, &D0, &L1ExtraUpgrade->et);
   FillObject(TkMHT, L1ExtraUpgrade->nTkMht, &L1ExtraUpgrade->tkMht, &D0, &L1ExtraUpgrade->tkMhtPhi, &L1ExtraUpgrade->tkMhtBx, &D0, &D0, &L1ExtraUpgrade->tkEt);

   return true;
}

void L1ExtraUpgradeTreeMessenger::FillObject(vector<GenericObject> &V, int N,
   vector<double> *ET, vector<double> *Eta, vector<double> *Phi, vector<int> *Bx,
   vector<double> *Iso, vector<double> *VZ, vector<double> *PET)
{
   V.clear();

   for(int i = 0; i < N; i++)
   {
      GenericObject O;

      double TempET = (ET->size() > i) ? (*ET)[i] : -1;
      double TempEta = (Eta->size() > i) ? (*Eta)[i] : -1;
      double TempPhi = (Phi->size() > i) ? (*Phi)[i] : -1;

      O.P.SetPtEtaPhi(TempET, TempEta, TempPhi);
      O.Bx = (Bx->size() > i) ? (*Bx)[i] : -1;
      O.Iso = (Iso->size() > i) ? (*Iso)[i] : -1;
      O.VZ = (VZ->size() > i) ? (*VZ)[i] : -1;
      O.PET = (PET->size() > i) ? (*PET)[i] : -1;

      V.push_back(O);
   }
}

void L1ExtraUpgradeTreeMessenger::FillObject(vector<GenericObject> &V, int N,
   vector<double> *ET, vector<double> *Eta, vector<double> *Phi, vector<double> *Bx,
   vector<double> *Iso, vector<double> *VZ, vector<double> *PET)
{
   V.clear();

   for(int i = 0; i < N; i++)
   {
      GenericObject O;

      double TempET = (ET->size() > i) ? (*ET)[i] : -1;
      double TempEta = (Eta->size() > i) ? (*Eta)[i] : -1;
      double TempPhi = (Phi->size() > i) ? (*Phi)[i] : -1;
      
      O.P.SetPtEtaPhi(TempET, TempEta, TempPhi);
      O.Bx = (Bx->size() > i) ? (*Bx)[i] : -1;
      O.Iso = (Iso->size() > i) ? (*Iso)[i] : -1;
      O.VZ = (VZ->size() > i) ? (*VZ)[i] : -1;
      O.PET = (PET->size() > i) ? (*PET)[i] : -1;

      V.push_back(O);
   }
}

