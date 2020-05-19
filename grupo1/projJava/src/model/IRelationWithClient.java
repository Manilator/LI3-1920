package model;

public interface IRelationWithClient {

    public void updateRelationWithClient(String client_code, int units, char promotion_type);
    int getTotalProductsSold();
}
